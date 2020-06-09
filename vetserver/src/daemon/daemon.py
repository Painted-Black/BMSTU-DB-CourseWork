from server.server import Server
from server.handlers.test_handler import TestHandler
from server.handlers.server_handlers import TableHandler
from database.dbaccess_manager import DBAccessManager, access_manager

class Daemon(object):
	def __init__(self, config):
		self.__config = config
		self.__server = Server()
		conn_info = self.__config.get_conn_info()
		repeat = self.__config.get_repeat_number()
		access_manager.init(conn_info, repeat)
		#self.__db=DBAccessManager(self.__config.get_conn_info())

	#def selftest(self):
		#return True

	def start(self):
		#self.__db.init()
		#self.__db.get_all_from("addresses")
		self.__server.add_endpoint(TableHandler())
		self.__server.start(port=self.__config.get_server_port())
