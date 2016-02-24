import unittest
import os
from minishell_tools import *
import sys


class Test21sh(unittest.TestCase):
	context = os.path.split(os.path.dirname(__file__))[0]
	minishell = "%s/minishell" % context
	testing_dir = "%s/tests/test_resources/" % context
	dotdot = "%sdotdot" % testing_dir
	valgrind_binary = False
	dev_null = open(os.devnull, 'w')
	queue = QueueProcess
	linux = True if "linux" in sys.platform else False
	tail = True if "TRUE" in "%s" % os.getenv("VG_TAIL") else False

	@classmethod
	def setUpClass(cls):
		os.chdir(cls.testing_dir)
		if subprocess.call(["make", "re", "-C", cls.context, "-j"], stdout=cls.dev_null) == 0:
			pass
		elif subprocess.call(["make", "-C", cls.context], stdout=cls.dev_null) == 0:
			os.write(2, "FAILED TO MAKE WITH -j")
		else:
			raise RuntimeError("compilation failed in %s" % cls.context)

		try:
			if subprocess.call(["valgrind", "--version"]) == 0:
				cls.valgrind_binary = True
		except OSError:
			os.write(2, "\nVALGRIND NOT AVAILABLE\n")
		os.chmod("%s/norights" % cls.testing_dir, 000)

	@classmethod
	def tearDownClass(cls):
		cls.dev_null.close()
		os.chmod("%s/norights" % cls.testing_dir, 0755)

	def execute_my_shell(self, command):
		"""
		Here my minishell
		:param command: list of command like ["/bin/ls", "-l"]
		:return:
		"""
		cmd_list = ["/bin/echo"] + command
		p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)

		p_minishell = subprocess.Popen(
				[self.minishell], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p_command.stdout.close()
		stdout, stderr = p_minishell.communicate()
		return stdout, stderr

	def execute_real_shell(self, command):
		"""
		Here the real shell
		:param command: list of command like ["/bin/ls", "-l"]
		:return:
		"""
		cmd_list = ["/bin/echo"] + command
		p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
		p_real_shell = subprocess.Popen(
				["/bin/bash"], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		p_command.stdout.close()
		stdout, stderr = p_real_shell.communicate()
		return stdout, stderr.replace("/bin/bash: line 1: ", "")  # because of bash piping

	def compare_returning_code(self, command):
		print subprocess.call(["/bin/echo"] + command + [self.minishell])

	def compare_shells(self, command):
		real_std = self.execute_real_shell(command)
		my_std = self.execute_my_shell(command)
		self.assertEqual(real_std, my_std)

	def valgrind(self, command):
		if self.valgrind_binary is True:
			leaks = QueueProcess(valgrind_wrapper, self.tail, self.minishell, command)
			leaks.start()

	def test_00(self):
		command = [
			"cd ..    ;   ls  test_resources | cat -e | rev | sort | cat -e > test_00_file ; cat test_00_file ; rm test_00_file"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_01(self):
		command = ["\n"]
		output = self.execute_my_shell(command)
		self.assertEqual(("", "ERROR not readable characters inside the buffer\n"), output)
		self.valgrind(command)

	def test_02(self):
		command = [
			" mkdir test_02_dir ; "
			"cd test_02_dir ; "
			"ls -a ; "
			"ls | cat | wc -c > fifi ; "
			"cat fifi ; "
			"cd .. ; "
			"rm -Rf test_02_dir; "
			"sleep 1"
		]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_03(self):
		command = [" cat test_03_nothere 2>&- "]
		self.compare_shells(command)
		self.valgrind(command)

	def test_04(self):
		command = [" /bin/cat test_04_nothere 2>&1 "]
		self.compare_shells(command)
		self.valgrind(command)

	def test_05(self):
		command = [" /bin/cat test_04_nothere 2>&1 | cat -e | rev"]
		self.compare_shells(command)
		self.valgrind(command)

	def test_06(self):
		command = [" /bin/ls notherefile |& cat -e"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_07(self):
		command = [" /bin/ls notherefile . |& cat -e"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_08(self):
		command = [" /bin/ls notherefile . 2>&1 |& cat -e"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_09(self):
		command = [" /bin/ls notherefile . 2>&1 |& cat -e  | cat -e |& cat -e"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_10(self):
		command = ["/bin/ls notherefile . 2>&1|&cat -e|cat -e|&cat -e"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_11(self):
		command = ["/bin/ls notherefile 2>&1|&cat -e|cat -e|&cat -e"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_12(self):
		command = ["/bin/ls notherefile|&cat -e|cat -e|&cat -e"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_13(self):
		command = ["/bin/ls -l notherefile .|&cat -e|cat -e|&cat -e|rev|sort|rev"]
		if self.linux:
			self.compare_shells(command)
		self.valgrind(command)

	def test_Z999Z_waiting_process(self):
		raising = []
		for p in self.queue.p:
			p.process.join()
			if p.process.exitcode != 0:
				raising.append(p.args)
		self.assertEqual([], raising)


if __name__ == "__main__":
	unittest.main()
