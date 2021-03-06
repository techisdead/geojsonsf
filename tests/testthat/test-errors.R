context("errors")

test_that("errors are handled", {

	expect_error(
		geojson_sf(1:5), "Geometry could not be determined"
		)
	expect_error(
		geojson_sf("a"), "Invalid JSON"
		)
	expect_error(
		geojson_sf()
		)
  expect_error(
  	geojson_sf(NULL)
  	)
  expect_error(
  	geojson_sf(NA), "Invalid JSON"
  	)
  expect_error(
  	geojson_sf('{ "type" : "Point" }'), "No 'coordinates' member at object index 0 - invalid GeoJSON"
  	)

  expect_error(
  	geojson_sf('{"type" : "MultiPoint","coordinates" : [0, 0] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_sf('{"type" : "Point", "coordinates" : null }'), "No 'array' member at object index 0 - invalid GeoJSON"
  	)
  expect_error(
  	geojson_sf('{"type" : "LineString", "coordinates" : [ 0, 0 ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_sf('{"type" : "MultiLineString", "coordinates" : [ 0, 0 ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_sf('{"type" : "MultiLineString", "coordinates" : [ [0, 0] ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_sf('{"type" : "Polygon", "coordinates" : [0, 0] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_sf('{"type" : "Polygon", "coordinates" : [ [ 0, 0 ] ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_sf('{"type" : "MultiPolygon", "coordinates" : [ [0, 0] ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_sf('{"type" : "MultiPolygon", "coordinates" : [ [ [0, 0] ] ] }'), "Invalid array object"
  	)

  expect_error(
  	geojson_wkt('{"type" : "LineString", "coordinates" : [ 0, 0 ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_wkt('{"type" : "MultiLineString", "coordinates" : [ 0, 0 ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_wkt('{"type" : "MultiLineString", "coordinates" : [ [0, 0] ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_wkt('{"type" : "Polygon", "coordinates" : [0, 0] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_wkt('{"type" : "Polygon", "coordinates" : [ [ 0, 0 ] ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_wkt('{"type" : "MultiPolygon", "coordinates" : [ [0, 0] ] }'), "Invalid array object"
  	)
  expect_error(
  	geojson_wkt('{"type" : "MultiPolygon", "coordinates" : [ [ [0, 0] ] ] }'), "Invalid array object"
  	)

  expect_error(
  	geojson_sf('{"type" : "Point" , "coordinates" : {} }'), "No 'array' member at object index 0 - invalid GeoJSON"
  	)

})
