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

	def get_ttl_key_hours(self):
		return int(self.__parser["SERVER"]["key_ttl_h"])

	def get_routes_auth(self):
		return [str(self.__parser["ROUTES"]["post_auth"])]

	def get_routes_schedule(self):
		return [str(self.__parser["ROUTES"]["post_schedule"])]

	def get_routes_short_animal_info(self):
		return [str(self.__parser["ROUTES"]["animal_short_info"])]

	def get_routes_short_client_info(self):
   		return [str(self.__parser["ROUTES"]["client_short_info"])]

	def get_routes_full_animal_info(self):
		return [str(self.__parser["ROUTES"]["animal_full_info"])]

	def get_routes_full_client_info(self):
		return [str(self.__parser["ROUTES"]["client_full_info"])]

	def get_routes_animal_upsert(self):
		return [str(self.__parser["ROUTES"]["animal_upsert_data"])]
		
	def get_routes_visit_new(self):
			return [str(self.__parser["ROUTES"]["new_visit"])]

	def get_routes_current_visits(self):
		return [str(self.__parser["ROUTES"]["current_visits"])]

	def get_routes_short_users_list(self):
		return [str(self.__parser["ROUTES"]["system_users_list"])]

	def get_routes_delete_user(self):
		return [str(self.__parser["ROUTES"]["delete_user"])]

	def get_routes_staff_short_info(self):
		return [str(self.__parser["ROUTES"]["staff_short"])]

	def get_routes_add_user(self):
		return [str(self.__parser["ROUTES"]["add_user"])]

	def get_routes_update_user(self):
		return [str(self.__parser["ROUTES"]["update_user"])]
	
	def get_routes_all_positions(self):
		return [str(self.__parser["ROUTES"]["all_positions"])]

	def get_routes_update_position(self):
		return [str(self.__parser["ROUTES"]["update_position"])]
	
	def get_routes_add_position(self):
		return [str(self.__parser["ROUTES"]["add_position"])]

	def get_routes_staff_full_info(self):
		return [str(self.__parser["ROUTES"]["full_staff_info"])]
	
	def get_routes_fire_staff(self):
		return [str(self.__parser["ROUTES"]["fire_staff"])]

	def get_routes_add_staff(self):
		return [str(self.__parser["ROUTES"]["add_staff"])]
	
	def get_routes_update_staff(self):
		return [str(self.__parser["ROUTES"]["update_staff"])]

	def get_conn_info(self):
		driver=self.__parser["DATABASE"]["driver"]
		server=self.__parser["DATABASE"]["server"]
		port=self.__parser["DATABASE"]["port"]
		dbname=self.__parser["DATABASE"]["dbname"]
		user=self.__parser["DATABASE"]["user"]
		password=self.__parser["DATABASE"]["password"]
		conn_info = DBConnInfo(driver, server, port, dbname, user, password)
		return conn_info