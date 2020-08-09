from abc import ABC
from abc import abstractmethod

from flask import Response
from flask import request

class AbstractHandler(ABC):
    
    def __call__(self):
        response = Response()
        self.request(request, response)
        return response

    @abstractmethod
    def _request(self, req, res):
        pass

    @abstractmethod
    def _endpoint_names(self):
        pass