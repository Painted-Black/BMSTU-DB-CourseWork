from server.server import Server
from server.handlers.test_handler import TestHandler
from server.handlers.auth_handler import AuthHandler
from server.handlers.schedule_handler import ScheduleHandler
from server.key_data_checker import KeyDataChecker
from server.key_data_checker import valid_key_checker
from database.dbaccess_manager import DBAccessManager, access_manager

class Daemon(object):
	def __init__(self, config):
		self.__config = config
		self.__server = Server()
		conn_info = self.__config.get_conn_info()
		repeat = self.__config.get_repeat_number()
		access_manager.init(conn_info, repeat)
		valid_key_checker.set_max_ttl_key(self.__config.get_ttl_key_hours())

		#self.__db=DBAccessManager(self.__config.get_conn_info())

	#def selftest(self):
		#return True

	def start(self):
		auth_=self.__config.get_routes_auth()
		schedule_=self.__config.get_routes_schedule()

		self.__server.add_endpoint(AuthHandler(auth_, ["POST"]))
		self.__server.add_endpoint(ScheduleHandler(schedule_, ["POST"]))
		self.__server.start(port=self.__config.get_server_port())
