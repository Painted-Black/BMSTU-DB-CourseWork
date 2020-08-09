from database.dbconn_info import DBConnInfo
import configparser
import argparse

class Config(object):
	def read_from_file(self, path):
		self.__parser = configparser.ConfigParser()
		if self.__parser.read(path).__len__ == 0:
			return False
		else:
			return True

	def get_server_port(self):
		return int(self.__parser["SERVER"]["port"])

	def get_repeat_number(self):
		return int(self.__parser["SERVER"]["repeat"])

	def get_conn_info(self):
		driver=self.__parser["DATABASE"]["driver"]
		server=self.__parser["DATABASE"]["server"]
		port=self.__parser["DATABASE"]["port"]
		dbname=self.__parser["DATABASE"]["dbname"]
		user=self.__parser["DATABASE"]["user"]
		password=self.__parser["DATABASE"]["password"]
		conn_info = DBConnInfo(driver, server, port, dbname, user, password)
		return conn_info