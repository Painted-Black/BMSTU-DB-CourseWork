from abc import ABC
from abc import abstractmethod

from flask import Response
from flask import request

class AbstractHandler(ABC):
    def __init__(self, routes : list, methods : list):
        self.routes=routes
        self.methods=methods

    def __call__(self):
        response = Response()
        self.request(request, response)
        return response

    @abstractmethod
    def request(self, req, res):
        pass

    def endpoint_names(self):
        return [self.routes, self.methods]