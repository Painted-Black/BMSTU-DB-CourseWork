from server.server import Server
from server.handlers.test_handler import TestHandler
from server.handlers.auth_handler import AuthHandler
from server.handlers.animal_handler import AnimalHandler
from server.handlers.client_handler import ClientHandler
from server.handlers.schedule_handler import ScheduleHandler
from server.handlers.new_visit_handler import NewVisitHandler
from server.handlers.current_visits_handler import CurrentVisitsHandler
from server.handlers.user_short_info_handler import UserShortInfoHandler
from server.handlers.add_user_handler import AddUserHandler
from server.handlers.delete_user_handler import DeleteUserHandler
from server.handlers.animal_info_handler import AnimalInfoHandler
from server.handlers.client_info_handler import ClientInfoHandler
from server.handlers.animal_upsert_handler import AnimalUpsertHandler
from server.key_data_checker import KeyDataChecker
from server.key_data_checker import valid_key_checker
from server.handlers.short_staff_info_handler import  ShortStaffInfo
from server.handlers.update_user_handler import UpdateUserHandler
from server.handlers.all_positions_handler import AllPositionsHandler
from server.handlers.update_position_handler import UpdatePositionHandler
from server.handlers.add_position_handler import AddPositionHandler
from server.handlers.staff_full_info_handler import FullStaffInfo
from server.handlers.photo_hanlder import PhotoHandler
from server.handlers.fire_staff_handler import FireStaffHandler
from server.handlers.add_staff_handler import AddStaffHandler
from server.handlers.update_staff_handler import UpdateStaffHandler
from server.handlers.all_schedules_handler import AllSchedulesHandler
from server.handlers.all_visits_handler import AllVisitsHandler
from server.handlers.visit_full_info_handler import VisitFullInfo

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
		animal_=self.__config.get_routes_short_animal_info()
		client_=self.__config.get_routes_short_client_info()
		animal_full_=self.__config.get_routes_full_animal_info()
		client_full_=self.__config.get_routes_full_client_info()
		new_visit_=self.__config.get_routes_visit_new()
		current_visit_=self.__config.get_routes_current_visits()
		users_short_=self.__config.get_routes_short_users_list()
		animal_upsert=self.__config.get_routes_animal_upsert()
		delete_user_=self.__config.get_routes_delete_user()
		staff_short_=self.__config.get_routes_staff_short_info()
		add_user_=self.__config.get_routes_add_user()
		update_user_=self.__config.get_routes_update_user()
		all_positions_=self.__config.get_routes_all_positions()
		update_position_=self.__config.get_routes_update_position()
		add_position_=self.__config.get_routes_add_position()
		staff_full_=self.__config.get_routes_staff_full_info()
		photo_path=self.__config.get_routes_photo()
		fire_staff_=self.__config.get_routes_fire_staff()
		add_staff_=self.__config.get_routes_add_staff()
		update_staff_=self.__config.get_routes_update_staff()
		all_schedules_=self.__config.get_routes_all_schedules()
		all_visits_short_=self.__config.get_routes_all_visits_short()
		visit_full_=self.__config.get_routes_visit_full()

		self.__server.add_endpoint(AuthHandler(auth_, ["POST"]))
		self.__server.add_endpoint(ScheduleHandler(schedule_, ["POST"]))
		self.__server.add_endpoint(AnimalHandler(animal_, ["GET"]))
		self.__server.add_endpoint(ClientHandler(client_, ["GET"]))
		self.__server.add_endpoint(AnimalInfoHandler(animal_full_, ["GET"]))
		self.__server.add_endpoint(ClientInfoHandler(client_full_, ["GET"]))
		self.__server.add_endpoint(NewVisitHandler(new_visit_, ["POST"]))
		self.__server.add_endpoint(CurrentVisitsHandler(current_visit_, ["POST"]))
		self.__server.add_endpoint(UserShortInfoHandler(users_short_, ["GET"]))
		self.__server.add_endpoint(AnimalUpsertHandler(animal_upsert, ["POST", "PUT"]))
		self.__server.add_endpoint(DeleteUserHandler( delete_user_, ["POST"]))
		self.__server.add_endpoint(ShortStaffInfo(staff_short_, ["GET"]))
		self.__server.add_endpoint(AddUserHandler(add_user_, ["POST"]))
		self.__server.add_endpoint(UpdateUserHandler(update_user_, ["POST"]))
		self.__server.add_endpoint(AllPositionsHandler(all_positions_, ["GET"]))
		self.__server.add_endpoint(UpdatePositionHandler(update_position_, ["POST"]))
		self.__server.add_endpoint(AddPositionHandler(add_position_, ["POST"]))
		self.__server.add_endpoint(FullStaffInfo(staff_full_, ["GET"]))
		self.__server.add_endpoint(PhotoHandler(photo_path, ["GET", "POST"], True))
		self.__server.add_endpoint(FireStaffHandler(fire_staff_, ["POST"]))
		self.__server.add_endpoint(AddStaffHandler(add_staff_, ["POST"]))
		self.__server.add_endpoint(UpdateStaffHandler(update_staff_, ["PUT"]))
		self.__server.add_endpoint(AllSchedulesHandler(all_schedules_, ["GET"]))
		self.__server.add_endpoint(AllVisitsHandler(all_visits_short_, ["GET"]))
		self.__server.add_endpoint(VisitFullInfo(visit_full_, ["GET"]))

		self.__server.start(port=self.__config.get_server_port())
