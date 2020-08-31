from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
import json
import uuid

class ScheduleHandler(AbstractHandler):
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

		status, data = self.__queryDb(staff_id)
		if not status:
			res.status_code=500
			return

		res.data = json.dumps(data)
		res.status_code=200

	def __to_json(self, rows, column_names):
		arr = []
		l = len(column_names)
		for i in rows:
			d = {}
			for j in range (l):
				d[column_names[j]] = str(i[j])
			arr.append(d)
		return arr

	def __queryDb(self, id : int):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = 'SELECT day_of_week, start, "end", cabinet FROM schedule s WHERE s.employee_id={};'.format(id)
		query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, ""
		else:
			result = query.get_values()

		access_manager.disconnect(conn_name)
		return True, self.__to_json(result, query.get_column_names())