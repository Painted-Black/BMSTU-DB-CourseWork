from abc import ABC
from abc import abstractmethod

from flask import Response
from flask import request

class AbstractHandler(ABC):
	def __init__(self, routes : list, methods : list, is_file=False):
		self.routes=routes
		self.methods=methods
		self.is_file=is_file

	def __call__(self):
		response = Response()
		if self.is_file == False:
			self.request(req=request, res=response)
			return response
		else:
			return self.request(req=request)

	@abstractmethod
	def request(self, **kwargs):
		pass

	def endpoint_names(self):
		return [self.routes, self.methods]
	
	def _to_json(self, rows, column_names):
		arr = []
		l = len(column_names)
		for i in rows:
			d = {}
			for j in range (l):
				d[column_names[j]] = str(i[j])
			arr.append(d)
		return arr