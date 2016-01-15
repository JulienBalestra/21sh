import unittest
import os
import subprocess


class TestAST(unittest.TestCase):
	context = os.path.split(os.path.dirname(__file__))[0]
	testing = os.path.dirname(__file__)
	mains = "%s/21sh_mains" % testing
	libsh = "%s/libsh.a" % context
	devnull = open("/dev/null", "w")
	bin = None

	@staticmethod
	def compilation(cl, main_test):
		bin_name = "%s" % main_test.replace(".c", ".bin")
		cmd = "gcc -Wall -Werror -Wextra {main} {libsha} -I {includessh} -I {includesft} {libfta} -o {output}".format(
				main="%s/%s" % (cl.mains, main_test),
				libsha="%s/libsh.a" % cl.context,
				includessh="%s/includes/" % cl.context,
				includesft="%s/libft/includes/" % cl.context,
				libfta="%s/libft/libft.a" % cl.context,
				output="%s/%s" % (cl.testing, bin_name))
		bin_path = "%s/%s" % (cl.testing, bin_name)
		assert subprocess.call(cmd.split(" ")) == 0
		assert os.path.isfile(bin_path) is True
		return bin_path

	@classmethod
	def setUpClass(cls):
		os.chdir("%s/test_resources" % cls.testing)
		assert subprocess.call(["make", "-C", cls.context], stdout=cls.devnull) == 0
		cls.bin = TestAST.compilation(TestAST, "main_ast.c")

	@classmethod
	def tearDownClass(cls):
		os.remove(cls.bin)

	def test_pipe_00(self):
		out = subprocess.check_output([self.bin, "/bin/ls -1 | /bin/cat -e"])
		self.assertEqual("file0$\nfile1$\n", out)

	def test_pipe_01(self):
		out = subprocess.check_output(["env", "DEBUG21=TRUE", self.bin, "/bin/ls -1 | /bin/cat -e"])
		expect = \
			"[ast_build][/ast_build]\n" \
			"[ast_read]/bin/cat -e | /bin/ls -1 [/ast_read]\n" \
			"[ast_exec]file0$\nfile1$\n[/ast_exec]\n" \
			"[ast_clean][/ast_clean]\n"
		self.assertEqual(expect, out)

	def test_pipe_02(self):
		out = subprocess.check_output([self.bin, "/bin/ls -1r | /bin/cat -e"])
		self.assertEqual("file1$\nfile0$\n", out)

	def test_pipe_03(self):
		out = subprocess.check_output([self.bin, "/bin/ls -1r | /bin/cat -e | /usr/bin/sort"])
		self.assertEqual("file0$\nfile1$\n", out)

	def test_pipe_04(self):
		out = subprocess.check_output([self.bin, "/bin/ls -1r | /bin/cat -e | /usr/bin/sort | /usr/bin/rev"])
		self.assertEqual("$0elif\n$1elif\n", out)

	def test_solo_00(self):
		out = subprocess.check_output([self.bin, "/bin/ls -1"])
		self.assertEqual("file0\nfile1\n", out)

	def test_right_00(self):
		out = subprocess.check_output([self.bin, "/bin/ls -1 > %s" % self.test_right_00.__name__])
		try:
			self.assertEqual("", out)
			with open("%s" % self.test_right_00.__name__, 'r') as f:
				self.assertEqual("file0\nfile1\n%s\n" % self.test_right_00.__name__, f.read())
		finally:
			os.remove("%s" % self.test_right_00.__name__)

	def test_right_01(self):
		out = subprocess.check_output([self.bin, "/bin/echo test0 > %s" % self.test_right_01.__name__])
		try:
			self.assertEqual("", out)
			with open("%s" % self.test_right_01.__name__, 'r') as f:
				self.assertEqual("test0\n", f.read())
		finally:
			os.remove("%s" % self.test_right_01.__name__)

	def test_double_right_00(self):
		out = subprocess.check_output([self.bin, "/bin/echo test1 >> %s" % self.test_double_right_00.__name__])
		try:
			self.assertEqual("", out)
			with open("%s" % self.test_double_right_00.__name__, 'r') as f:
				self.assertEqual("test1\n", f.read())
		finally:
			os.remove("%s" % self.test_double_right_00.__name__)

	def test_double_right_01(self):
		out0 = subprocess.check_output([self.bin, "/bin/echo base0 >> %s" % self.test_double_right_01.__name__])
		with open("%s" % self.test_double_right_01.__name__, 'r') as f:
			self.assertEqual("base0\n", f.read())
		out1 = subprocess.check_output([self.bin, "/bin/echo base1 >> %s" % self.test_double_right_01.__name__])
		try:
			self.assertTrue(out0 == out1 == "")
			with open("%s" % self.test_double_right_01.__name__, 'r') as f:
				self.assertEqual("base0\nbase1\n", f.read())
		finally:
			os.remove("%s" % self.test_double_right_01.__name__)

	def test_double_right_pipe_00(self):
		out0 = subprocess.check_output(
				[self.bin, "/bin/echo base0 | /bin/cat -e >> %s" % self.test_double_right_pipe_00.__name__])
		with open("%s" % self.test_double_right_pipe_00.__name__, 'r') as f:
			self.assertEqual("base0$\n", f.read())
		out1 = subprocess.check_output([self.bin, "/bin/echo base1 >> %s" % self.test_double_right_pipe_00.__name__])
		try:
			self.assertTrue(out0 == out1 == "")
			with open("%s" % self.test_double_right_pipe_00.__name__, 'r') as f:
				self.assertEqual("base0$\nbase1\n", f.read())
		finally:
			os.remove("%s" % self.test_double_right_pipe_00.__name__)

	def test_double_right_pipe_01(self):
		out0 = subprocess.check_output([self.bin,
										"/bin/echo base0 | /bin/cat -e | /usr/bin/rev >> %s" % self.test_double_right_pipe_00.__name__])
		with open("%s" % self.test_double_right_pipe_00.__name__, 'r') as f:
			self.assertEqual("$0esab\n", f.read())
		out1 = subprocess.check_output(
				[self.bin,
				 "/bin/echo base1 | /bin/cat -e | /usr/bin/rev >> %s" % self.test_double_right_pipe_00.__name__])
		try:
			self.assertTrue(out0 == out1 == "")
			with open("%s" % self.test_double_right_pipe_00.__name__, 'r') as f:
				self.assertEqual("$0esab\n$1esab\n", f.read())
		finally:
			os.remove("%s" % self.test_double_right_pipe_00.__name__)

	def test_left_00(self):
		out = subprocess.check_output([self.bin, "/bin/cat < file0"])
		self.assertEqual("ok", out)
		# safety below
		with open("file0", 'r') as f:
			self.assertEqual("ok", f.read())
