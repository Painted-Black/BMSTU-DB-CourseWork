from .abstract_handler import AbstractHandler
import json

from flask import request

class TestHandler(AbstractHandler):
	def request(self, req, res):
		res.status_code = 200
		out = req.args.get('user')
		res.data = json.dumps({"Successful": out})
		res.content_type = "Application/Json"
		print(req.data)

	def endpoint_names(self):
		return ["/test"]