// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/geojsonsf.h"
#include <Rcpp.h>

using namespace Rcpp;

// rcpp_geojson_to_sfc
Rcpp::List rcpp_geojson_to_sfc(Rcpp::StringVector geojson);
RcppExport SEXP _geojsonsf_rcpp_geojson_to_sfc(SEXP geojsonSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geojson(geojsonSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geojson_to_sfc(geojson));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_geojson_to_sf
Rcpp::List rcpp_geojson_to_sf(Rcpp::StringVector geojson);
RcppExport SEXP _geojsonsf_rcpp_geojson_to_sf(SEXP geojsonSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geojson(geojsonSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geojson_to_sf(geojson));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_geojson_to_wkt
Rcpp::List rcpp_geojson_to_wkt(Rcpp::StringVector geojson);
RcppExport SEXP _geojsonsf_rcpp_geojson_to_wkt(SEXP geojsonSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type geojson(geojsonSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geojson_to_wkt(geojson));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_geojsonsf_rcpp_geojson_to_sfc", (DL_FUNC) &_geojsonsf_rcpp_geojson_to_sfc, 1},
    {"_geojsonsf_rcpp_geojson_to_sf", (DL_FUNC) &_geojsonsf_rcpp_geojson_to_sf, 1},
    {"_geojsonsf_rcpp_geojson_to_wkt", (DL_FUNC) &_geojsonsf_rcpp_geojson_to_wkt, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_geojsonsf(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
