#include "geojson_wkt.h"
#include "sf_geojson.h"

#include <Rcpp.h>
using namespace Rcpp;

template <int RTYPE>
Rcpp::CharacterVector sfClass(Vector<RTYPE> v) {
	return v.attr("class");
}

Rcpp::CharacterVector getSfClass(SEXP sf) {

	switch( TYPEOF(sf) ) {
	case REALSXP:
		return sfClass<REALSXP>(sf);
	case VECSXP:
		return sfClass<VECSXP>(sf);
	case INTSXP:
		return sfClass<INTSXP>(sf);
	default: Rcpp::stop("unknown sf type");
	}
	return "";
}


void get_column_type(Rcpp::List& sf, Rcpp::StringVector& property_names, Rcpp::StringVector& column_types) {

	//int counter = 0;
	//for (Rcpp::List::iterator it = sf.begin(); it != sf.end(); it++) {
	for (int i = 0; i < property_names.size(); i++) {

		Rcpp::String col = property_names[i];
		SEXP vec = sf[col];

		switch(TYPEOF(vec)) {
		case REALSXP:
			//Rcpp::Rcout << "REAL Number" << std::endl;
			column_types[i] = "Number";
			break;
		//case VECSXP:
		//	Rcpp::Rcout << "Number" << std::endl;
		//	break;
		case INTSXP:
			//Rcpp::Rcout << "INT Number" << std::endl;
			column_types[i] = "Number";
			break;
		case LGLSXP:
			//Rcpp::Rcout << "LGL Logical" << std::endl;
			column_types[i] = "Logical";
			break;
		default: {
				//Rcpp::Rcout << "default: String" << std::endl;
				column_types[i] = "String";
				break;
		}
		}
	}
}
/*
void add_geometrycollection_to_stream(std::ostringstream& os, Rcpp::List& gc) {
	os << "\"GeometryCollection\" , \"geometries\" : [";
	// recurse into gc object
	Rcpp::List gci(1);
	for (int i = 0; i < gc.size(); i++) {
		gci[0] = gc[i];
		fetch_coordinates(os, gci);
		object_separator(os);
	}
	os << "]}";
}
*/
void begin_geojson_geometry(std::ostringstream& os, std::string& geom_type) {
    Rcpp::List sfc;
	  begin_geojson_geometry(os, sfc, geom_type);
}

// Stream an SF object to GeoJSON
void begin_geojson_geometry(std::ostringstream& os, Rcpp::List& sfc, std::string& geom_type) {
	os << "{\"type\" : ";
	if (geom_type == "POINT") {
		os <<  "\"Point\" , \"coordinates\" : ";
	} else if (geom_type == "MULTIPOINT") {
		os << "\"MultiPoint\" , \"coordinates\" : [";
	} else if (geom_type == "LINESTRING") {
		os << "\"LineString\" , \"coordinates\" : [";
	} else if (geom_type == "MULTILINESTRING") {
		os << "\"MultiLineString\" , \"coordinates\" : [[";
	} else if (geom_type == "POLYGON") {
		os << "\"Polygon\" , \"coordinates\" : [[";
	} else if (geom_type == "MULTIPOLYGON") {
		os << "\"MultiPolygon\" , \"coordinates\" : [[[";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		//add_geometrycollection_to_stream(os, sfc);
		os << "\"GeometryCollection\" , \"geometries\" : [";
	}
}

void end_geojson_geometry(std::ostringstream& os, std::string& geom_type) {
	if (geom_type == "POINT") {
		os << "}";
	} else if (geom_type == "MULTIPOINT") {
		os << "]}";
	} else if (geom_type == "LINESTRING") {
		os << "]}";
	} else if (geom_type == "MULTILINESTRING") {
		os << "]]}";
	} else if (geom_type == "POLYGON") {
		os << "]]}";
	} else if (geom_type == "MULTIPOLYGON") {
		os << "]]]}";
	} else if (geom_type == "GEOMETRYCOLLECTION") {
		os << "]}";
	}
}

void add_lonlat_to_stream(std::ostringstream& os, Rcpp::NumericVector& points) {

	points.attr("dim") = Dimension(points.size() / 2, 2);
	Rcpp::NumericMatrix m = as< Rcpp::NumericMatrix >(points);

	for (int i = 0; i < m.nrow(); i++) {
		os << "[" << m(i, 0) << "," << m(i, 1) << "]";
		coord_separator(os, i, m.nrow());
	}
}

void fetch_coordinates(std::ostringstream& os, Rcpp::List& sfc, int& object_counter) {

	//Rcpp::Rcout << "debug object_couter: " << object_counter << std::endl;

	//Rcpp::Rcout << "debug: sfc size: " << sfc.size() << std::endl;
	//os << "[";
	//bracket_counter++;
	//Rcpp::Rcout << "type sfc: " << TYPEOF(sfc) << std::endl;
	Rcpp::CharacterVector cls;
	std::string geom_type;

	for (Rcpp::List::iterator it = sfc.begin(); it != sfc.end(); it++) {

		if (object_counter > 0) {
			object_separator(os);
		}

		switch( TYPEOF(*it) ) {
		case VECSXP: {
			Rcpp::List tmp = as<Rcpp::List>(*it);
			if(!Rf_isNull(tmp.attr("class"))) {

				// if there's a 'class' attribute, it's an sfg object
				// but it's also a list
				// so need to go through the list elemetns and fetch the geometries
				//
				// but, if the list is a 'GEOMETRYCOLLECTION', we need a ',' separator
				// after each geometry

				//Rcpp::Rcout << "debug list " << std::endl;
				cls = getSfClass(tmp);
				geom_type = cls[1];    // TODO: error handle (there should aways be 3 elements as we're workgin wtih sfg objects)
				begin_geojson_geometry(os, tmp, geom_type);
			  fetch_coordinates(os, tmp, object_counter);
			  end_geojson_geometry(os, geom_type);
			} else {
				// if no class attribute, go further into the list to try and find one
				fetch_coordinates(os, tmp, object_counter);
			}
			//Rcpp::Rcout << "debug: updating object_counter" << std::endl;
			object_counter++;
			//Rcpp::Rcout << "debug object_couter: " << object_counter << std::endl;
			break;
		}
		case REALSXP: {
			Rcpp::NumericVector tmp = as<Rcpp::NumericVector>(*it);
			if(!Rf_isNull(tmp.attr("class"))) {
				//Rcpp::Rcout << "debug vector " << std::endl;
				cls = getSfClass(tmp);
				geom_type = cls[1];
				begin_geojson_geometry(os, geom_type);
			  add_lonlat_to_stream(os, tmp);
			  end_geojson_geometry(os, geom_type);
			} else {
				add_lonlat_to_stream(os, tmp);
			}
			//Rcpp::Rcout << "debug: updating object_counter" << std::endl;
			object_counter++;
			//Rcpp::Rcout << "debug object_couter: " << object_counter << std::endl;
			break;
		}
		case INTSXP: {
			//Rcpp::IntegerVector tmp = as<Rcpp::IntegerVector>(*it);
			//add_lonlat_to_stream(os, tmp);
			break;
		}
		default: {
			Rcpp::stop("Coordinates could not be found");
		}
	  }
	}
}


void add_geometry_to_stream(std::ostringstream& os, Rcpp::List& sfc) {
	//Rcpp::Rcout << "debug: resetting object_counter" << std::endl;
	int object_counter = 0;
  fetch_coordinates(os, sfc, object_counter);
}

// if only one object with properties, it's a 'feature'
// if only one object without properties, it's a 'geometry'
// if many objects it's a 'featurecollection'


void sfg_to_geojson(std::ostringstream& os, Rcpp::List& sfc) {
	Rcpp::CharacterVector cls;
	std::string geom_type;
	Rcpp::List sfci(1);
	Rcpp::List sfg_geojson(sfc.size());
	for (int i = 0; i < sfc.size(); i++) {
		// iff 'atomise'; return a StringVector of each geometry
		// iff not, return an array of each vecor

		sfci[0] = sfc[i];
		add_geometry_to_stream(os, sfci);
		coord_separator(os, i, sfc.size());
	}
}

void sfc_to_geojson(std::ostringstream& os, Rcpp::List& sfc) {
	sfg_to_geojson(os, sfc);
}

Rcpp::StringVector rcpp_sfg_to_geojson(Rcpp::List sfg) {
	std::ostringstream os;
	sfg_to_geojson(os, sfg);
	return os.str();
}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sfc_to_geojson(Rcpp::List sfc) {
	std::ostringstream os;
	sfc_to_geojson(os, sfc);
	return os.str();
}


void properties_to_json(std::ostringstream& os, Rcpp::List sf_row) {
	// iterate over rows and add to JSON stream

}


//void get_column_types(Rcpp::StringVector& column_types, Rcpp::List& sf) {
//  for (int i = 0; i < sf.ncol(); i++) {
//  	column_types[i] = get_column_type(sf[i]);
//  	//Rcpp::Rcout << "debug: column type: " << column_types[i] << std::endl;
//  }
//}

// [[Rcpp::export]]
Rcpp::StringVector rcpp_sf_to_geojson(Rcpp::List sf) {

	std::ostringstream os;
	// If it contains properties
	// it's a 'feature' (or featureCollection)
	//
	// if 'atomise', return one object per row

	Rcpp::StringVector column_types(sf.size() - 1);
	//get_column_type(sf, column_types);
	Rcpp::StringVector property_names(sf.size() - 1);

	std::string geom_column = sf.attr("sf_column");
	Rcpp::StringVector col_names = sf.names();

	// fill 'property_names' with all the columns which aren't 'sf_column'
	int property_counter = 0;
	for (int i = 0; i < sf.length(); i++) {
		if (col_names[i] != geom_column) {
			property_names[property_counter] = col_names[i];
			property_counter++;
		}
	}

	get_column_type(sf, property_names, column_types);
	Rcpp::Rcout << "debug property names : " << property_names << std::endl;
	Rcpp::Rcout << "debug column types : " << column_types << std::endl;

	Rcpp::List sfc = sf[geom_column];
	Rcpp::List properties;

	// TODO:
	// construct a StringMatrix with the dimensions of sf
	// then I can fill a column at a time with a string of JSON...
	// then can manipulate it as I want at the end; either atomising or combining
	Rcpp::NumericMatrix json_mat(sfc.length(), sf.size()); // row x cols
	for (int i = 0; i < sf.size(); i++) {
		// iterate the list elements
		for (int j = 0; j < sfc.length(); j++) {
			// iterate each row
			// construct a string of the property { name : value }


			// TODO: what if there's a mssing element?

		}
	}


	sfc_to_geojson(os, sfc);

	// iterate over each row of sf
	// - properties to js
	// - geometry to sf
	// - combine
	// IFF atomise, assign os.str() to result vector
	// ELSE, don't.

	Rcpp::StringVector res = os.str();

	return res;
}


