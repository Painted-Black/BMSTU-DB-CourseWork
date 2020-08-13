from flask import Flask
from flask import request
from flask import Response

class Server(object):
    def __init__(self):
        self.__app = Flask("Vetserver")

    def start(self, port):
        self.__app.run(port=port)

    def add_endpoint(self, handler):
        names = handler.endpoint_names()
        routes = names[0]
        methods = names[1]
        for i in routes:
            self.__app.add_url_rule(i, i.replace('/', '_'), view_func=handler, methods=methods)