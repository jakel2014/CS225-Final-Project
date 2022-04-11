#!/usr/bin/env python3
# usage: import-routes <airports CSV> <routes CSV>

OUTPUT_FILE = 'routes-preprocessed.csv'

import csv
import sys

# import airports
airports = {}
with open(sys.argv[1], encoding = 'utf-8') as f_airports_csv:
	reader = csv.reader(f_airports_csv)
	for row in reader:
		ID = row[0]
		airports[ID] = {
			#'ID': row[0],
			'name': row[1],
			'IATA': row[4],
			'ICAO': row[5],
			'latitude': row[6],
			'longitude': row[7]
		}

# import routes
with open(OUTPUT_FILE, 'w', encoding = 'utf-8') as f_out:
	writer = csv.writer(f_out)
	writer.writerow([
		'src airport ID', 'src airport lat', 'src airport long',
		'dst airport ID', 'dst airport lat', 'dst airport long'])
	with open(sys.argv[2], encoding = 'utf-8') as f_routes_csv:
		reader = csv.reader(f_routes_csv)
		for row in reader:
			stops = int(row[7])
			if stops != 0:
				# skip non-direct routes
				continue
			src_airport_ID = row[3]
			dst_airport_ID = row[5]
			if src_airport_ID == '\\N' or dst_airport_ID == '\\N':
				# skip if we don't know the source or the destination
				continue
			try:
				src_airport = airports[src_airport_ID]
				dst_airport = airports[dst_airport_ID]
			except KeyError:
				# skip routes involving undefined airports
				continue
			src_airport_lat  = src_airport['latitude']
			src_airport_long = src_airport['longitude']
			dst_airport_lat  = dst_airport['latitude']
			dst_airport_long = dst_airport['longitude']
			writer.writerow([
				src_airport_ID, src_airport_lat, src_airport_long,
				dst_airport_ID, dst_airport_lat, dst_airport_long])
