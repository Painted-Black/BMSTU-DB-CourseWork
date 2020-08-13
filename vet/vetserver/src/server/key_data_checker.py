from config.config import Config
import datetime


class KeyDataChecker(object):
    def __init__(self):
        self.data = {}
        self.ttl = -1


    def set_max_ttl_key(self, ttl):
        self.ttl = ttl

    def register_key(self, key : str, owner : int):
        if self.data.__contains__(key):
            return False

        self.data[key]=(owner, datetime.datetime.now())
        return True

    def get_owner(self, key):
        if not self.data.__contains__(key):
            return -1

        return int(self.data[key][0])
        

valid_key_checker = KeyDataChecker()