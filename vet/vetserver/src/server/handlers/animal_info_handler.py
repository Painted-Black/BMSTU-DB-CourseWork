from .abstract_handler import AbstractHandler
from .utils import *

from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker

import json
import uuid


class AnimalInfoHandler(AbstractHandler):
	def request(self, req, res):
		key = str(req.headers.get("Authorization"))
		# Authorization: Explicit Key
		explicit_key="Explicit: "
		idx = key.find(explicit_key) 
		if idx == -1:
			res.status_code=401
			return
		
		key = key[len(explicit_key):]
		staff_id = valid_key_checker.get_owner(key)
		if staff_id == -1:
			res.status_code=401
			return

		id = request.args.get("id", default=None, type=None)
		status, data = self.__queryDb(id)
		if not status:
			res.status_code=500
			return

		res.data = json.dumps(data)
		res.status_code=200

	def __queryDb(self, id : int):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = 'SELECT * FROM animals_medical_records WHERE anim_id={};'.format(id)
		query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.to_json(result, query.get_column_names())