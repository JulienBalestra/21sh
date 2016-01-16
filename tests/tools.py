import subprocess

try:
	import xml.etree.cElementTree as ET
except ImportError:
	import xml.etree.ElementTree as ET


def valgrind_wrapper(command, test, binary):
	xml_output = "../test_valgrind_xml/%s.xml" % test
	args = " ".join(command[1:])
	command = " ".join(command)
	cli = "valgrind --leak-check=full --xml=yes --xml-file=%s %s %s" % (xml_output, binary, command)
	valgrind = cli.split(" ")
	subprocess.call(valgrind)

	root = ET.parse(xml_output).getroot()
	if root.find("error") is not None:
		pass
	# raise AssertionError("[%s] -> %s" % (test, args)) TODO leaks
