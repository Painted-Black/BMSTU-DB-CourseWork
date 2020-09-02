import argparse

class ConfigArgs(object):
	@staticmethod
	def fromArgs():
		cfg = ConfigArgs()
		parser = argparse.ArgumentParser()
		parser.add_argument('-c', metavar='config_path', help='path to configuration file')
		args = parser.parse_args()
		cfg.setConfigFile(args.c)
		return cfg

	def setConfigFile(self, path):
		self.cfg_path = path

	def getConfigFile(self):
		return self.cfg_path