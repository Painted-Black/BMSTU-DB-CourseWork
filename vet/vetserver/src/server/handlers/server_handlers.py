from .abstract_handler import AbstractHandler
import json
import uuid

from flask import request

from database.dbaccess_manager import access_manager
from database.dbquery import DBQuery

class TableHandler(AbstractHandler):
	def request(self, req, res):
		res.status_code = 200
		out = req.args.get('tablename')
		state, data, colunm_names = self.__table_query(out)
		if not state:
			res.status_code = 500
			return
		else:
			res.content_type = "Application/Json"
			res.data = self.__to_json(data, colunm_names)
	
	def __to_json(self, rows, column_names):
		arr = []
		l = len(column_names)
		for i in rows:
			d = {}
			for j in range (l):
				d[column_names[j]] = i[j]
			arr.append(d)
		print(arr)
		return json.dumps(arr)
		

	def __table_query(self, tablename):
		conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)
		str_query = 'SELECT * FROM {}'.format(tablename)
		query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, None
		else:
			result = query.get_values()
			column_names = query.get_colunm_names()
		access_manager.disconnect(conn_name)
		return True, result, column_names



	def endpoint_names(self):
		return [["/table/all"], ['GET']]