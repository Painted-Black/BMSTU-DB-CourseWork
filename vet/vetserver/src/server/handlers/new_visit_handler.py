from .abstract_handler import AbstractHandler
from database.dbconn import DBConn
from database.dbquery import DBQuery
from database.dbaccess_manager import access_manager
from server.key_data_checker import valid_key_checker
from server.utils.animal_state import AnimalState
import json
import uuid
from flask import request
from server.utils.visit import Visit

class NewVisitHandler(AbstractHandler):
    def request(self, req, res):
		res.content_type = "Application/Json"
        try:
			json_data = json.loads(req.data)
		except json.decoder.JSONDecodeError:
			res.status_code=403
			res.data = json.dumps({"error" : "Empty json"})
			return

        if not self.check_json(json_data):
            res.status_code=403
			res.data = json.dumps({"error" : "Expected values was not received"})
			return

        vis = Visit()
        vis.deserialize(json_data)
        anim_state = AnimalState()
        anim_state.deserialize(json_data)
        state, state_id = self.__insert_state_to_db(anim_state))
        if (not state):
			res.status_code=500
			res.data = json.dumps({"error" : "insertion (animal_state) failed"})
			return
        vis.set_cur_state(state_id)
        
        state = self.__insert_visit_to_json(vis)
        if not state:
            res.status_code=500 #TODO
			res.data = json.dumps({"error" : "insertion (visit) failed"})
			return
    
    def __insert_visit_to_json(self, state_id : Visit):
        conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

        if access_manager.is_valid() == False:
            return False, None
        
        str_query = \
            '''INSERT INTO visits (doctor, animal, ambulatury, visit_date, owner_dynamics, history_disease, cur_state, diagnosis, recommendations, next_visit, prescribings, initial, note) VALUES ({}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {});'''.format(vis.get_doctor(), vis.get_animal(), vis.get_ambulatory(), vis.get_visit_date(), vis.get_owner_dynamics(), vis.get_history_disease(), vis.get_cur_state(), vis.get_diagnosis(), vis.get_recommendations(), vis.get_next_visit(), vis.get_prescribings(), vis.get_initial(), vis.get_note())

        query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False
		else:
			result = query.get_values()

		if len(result) == 0:
			return False

		access_manager.disconnect(conn_name)
		return True

    def __insert_state_to_db(self, animal_state : AnimalState):
        conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

        if access_manager.is_valid() == False:
            return False, None

        str_query = \
            '''INSERT INTO animal_states (general, pulse, weight, ap, temperature, cfr, resp_rate) VALUES ({}, {}, {}, {}, {}, {}, {}) RETURNING state_id;'''.format(animal_state.get_general, animal_state.get_pulse(), animal_state.get_weight(), animal_state.get_ap(),
            animal_state.get_temperature(), animal_state.get_cfr(), animal_state.get_resp_rate())

        query = DBQuery(conn, str_query)
		if not query.execQuery():
			return False, None
		else:
			result = query.get_values()
        if len(result) == 0:
			return False, None

		access_manager.disconnect(conn_name)

        return True, str(result[0][0])

    def check_json(self, json_data):
        return json_data.__contains__('doctor') and json_data.__contains__('animal') and json_data.__contains__('ambulatury') and json_data.__contains__('visit_date') and json_data.__contains__('owner_dynamics') and json_data.__contains__('history_disease') and json_data.__contains__('cur_state') and json_data.__contains__('diagnosis') and json_data.__contains__('recommendations') and json_data.__contains__('next_visit') and json_data.__contains__('prescribings') and json_data.__contains__('initial') and json_data.__contains__('note')
        