require 5.002;

use File::Copy;
use strict;
use Socket;
use Carp;
use FileHandle;

# Used to generate resource headers and defines from the currencies.h table.
# We have do this since the resource compiler has very limited support
# of pre-processor directives.

sub MakeDefines
{
	my($tableFile, $headerFile) = @_;
	my($id) = 400; # start string resource IDs at 400

	open TABLE, "<$tableFile" or die "cannot open file \"$tableFile\" for input\n";
	open HEADER, ">$headerFile" or die "cannot open file \"$headerFile\" for output\n";

	print HEADER "#pragma once\n";
	print HEADER "// Don't modify this file.\n";
	print HEADER "// This file is generated from makedefines.pl\n";
	print HEADER "// If you change currencies.h, you need to\n";
	print HEADER "// run maketables.pl to regenerate this file.\n";

	while(<TABLE>)
		{
		if(/DEFINE_CURRENCY\(([^\s,]*)[\s,]*\"([^\"]*)[\"\s,]*([0123456789.]*)/)
			{
			print HEADER "#define IDS_CUR_$1  $id\n";
			$id++; 
			}
		}

	close HEADER;
	close TABLE;
}

sub MakeResources
{
	my($tableFile, $headerFileName, $resourceFile) = @_;
	my($id) = 400; # start string resource IDs at 400

	open TABLE, "<$tableFile" or die "cannot open file \"$tableFile\" for input\n";
	open RESOURCE, ">$resourceFile" or die "cannot open file \"$resourceFile\" for output\n";

	print RESOURCE "#include \"$headerFileName\"\n";
	print RESOURCE "// Don't modify this file.\n";
	print RESOURCE "// This file is generated from makedefines.pl\n";
	print RESOURCE "// If you change currencies.h, you need to\n";
	print RESOURCE "// run maketables.pl to regenerate this file.\n";
 
	print RESOURCE "STRINGTABLE DISCARDABLE\n";
	print RESOURCE "BEGIN\n";

	while(<TABLE>)
		{
		if(/DEFINE_CURRENCY\(([^\s,]*)[\s,]*\"([^\"]*)[\"\s,]*([0123456789.]*)/)
			{
			print RESOURCE "    IDS_CUR_$1  \"$2\"\n";
			$id++; 
			}
		}
	print RESOURCE "END\n";

	close RESOURCE;
	close TABLE;
}

my($tableFileName) = "currencies.h";
my($headerFileName) = "cur.h";
my($resourceFileName) = "cur.rc";

MakeDefines($tableFileName, $headerFileName);
MakeResources($tableFileName, $headerFileName, $resourceFileName);

exit;
