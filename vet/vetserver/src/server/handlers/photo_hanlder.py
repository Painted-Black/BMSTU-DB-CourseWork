from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
from server.utils.animal_state import AnimalState
import json
import uuid
from server.utils.visit import Visit
import os
from flask import Response
from flask import send_file

class PhotoHandler(AbstractHandler):
	def request(self, req):
		key = str(req.headers.get("Authorization"))
		# Authorization: Explicit Key
		explicit_key="Explicit: "
		idx = key.find(explicit_key) 
		if idx == -1:
			res = Response()
			res.status_code=401
			return res
		
		key = key[len(explicit_key):]
		staff_id = valid_key_checker.get_owner(key)
		if staff_id == -1:
			res = Response()
			res.status_code=401
			return

		path_to = os.path.join(os.path.abspath(os.curdir), "server", "data", "images")	
		img=req.args.get('img', default=None, type=None)

		if req.method == 'GET':
			for i in os.listdir(path_to):
				if i == img:
					file=i
					return send_file(os.path.join(path_to, file))
		else:
			res = Response()
			header = str(req.headers.get("Content-Type"))
			ext : str
			if header == "image/jpeg":
				ext="jpeg"
			elif header == "image/png":
				ext="png"
			else:
				res.status_code = 400
				return res

		res.status_code = 201
		filename = str(uuid.uuid4()) + '.' + ext
		file = open(os.path.join(path_to, filename), 'wb');
		file.write(req.data)
		file.close()
		res.content_type="plain/text"
		res.data = filename
		return res



			
