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

        anim_st = self.__get_state_from_json(json_data)
        visit = self.__get_visit_from_json(json_data)
        state, data = self.__insert_state_to_db(anim_st)

    def __get_state_from_json(self, json):
        state = AnimalState()
        state.set_general(json['general'])
        state.set_pulse(json['pulse'])
        state.set_weight(json['weight'])
        state.set_ap(json['ap'])
        state.set_temperature(json['temperature'])
        state.set_cfr(json['cfr'])
        state.set_resp_rate(json['resp_rate'])
        return state

    def __get_visit_from_json(self, json):
        vis = Visit()
        vis.set_doctor(json['doctor'])
        vis.set_animal(json['animal'])
        vis.set_ambulatory(json['ambulatury'])
        vis.set_visit_date(json['visit_date'])
        vis.set_owner_dynamics(json['owner_dynamics']
        vis.set_history_disease(json['history_disease'])
        vis.set_cur_state(json['cur_state'])
        vis.set_diagnosis(json['diagnosis'])
        vis.set_recommendations(json['recommendations'])
        vis.set_next_visit(json['next_visit'])
        vis.set_prescribings(json['prescribings'])
        vis.set_initial(json['initial'])
        vis.set_note(json['note'])
        return vis

    def __insert_state_to_db(self, animal_state : AnimalState):
        conn_name = str(uuid.uuid4())
		conn = access_manager.connect(conn_name)

        if access_manager.is_valid() == False:
            return False, None

        str_query = \
            '''INSERT INTO animal_states (general, pulse, weight, ap, temperature, cfr, resp_rate) VALUES ({}, {}, {}, {}, {}, {}, {}) RETURNING state_id'''.format(animal_state.get_general, animal_state.get_pulse(), animal_state.get_weight(), animal_state.get_ap(),
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
        #self.__to_json_state_id(result, query.get_column_names())
    
    #def __to_json_state_id(self, rows, column_names):
    #    out_json = {}
	#	row = rows[0]
    #    out_json[column_names[0]] = str(row[0])
    #    return

    def check_json(self, json_data):
        return True
        # TODO