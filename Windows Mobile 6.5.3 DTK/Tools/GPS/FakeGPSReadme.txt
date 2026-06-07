FAKE GPS
========
Copyright(c) 2005 Microsoft Corporation 

Fake GPS enables developers to receive data using the GPS APIs even if there is no GPS receiver on the device.
The GPS data is read from NMEA .txt files that get deployed to \Program Files\FakeGPS\GPSFiles when FakeGPS.CAB is installed on the device.

Fake GPS must run in privileged mode because it interacts with the GPS intermediate driver and writes to the privileged area of the registry.

Fake GPS ships with a couple of sample data files:
dixies.txt - NMEA files that immediately starts sending a GPS location to the GPS driver.
fakegpsdata.txt - Same as dixies.txt, but it takes some time to report a new location.
