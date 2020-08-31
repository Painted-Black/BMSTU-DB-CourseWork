from .animal_state import AnimalState

class Visit():
    def __init__(self):
        self.__vis_id = None
        self.__doctor = None
        self.__animal = None
        self.__ambulatory = None
        self.__visit_date = None
        self.__owner_dynamics = None
        self.__history_disease = None
        self.__cur_state = None
        self.__diagnosis = None
        self.__recommendations = None
        self.__next_visit = None
        self.__prescribings = None
        self.__initial = None
        self.__note = None

    def deserialize(self, json):
        self.__doctor = json['doctor']
        self.__animal = json['animal']
        self.__visit_date = json['visit_date']
        self.__owner_dynamics = json['owner_dynamics']
        self.__history_disease = json['history_disease']
        #self.__cur_state.deserialize(json['cur_state'])
        self.__diagnosis = json['diagnosis']
        self.__recommendations = json['recommendations']
        self.__next_visit = json['next_visit']
        self.__prescribings = json['prescribings']
        self.__note = json['note']

    def is_valid(self):
        #TODO check date is valid 
        try:
            res =  ( self.__vis_id >= 0 and self.__doctor >= 0 and self.__animal >= 0 and (self.__ambulatory == 'true' or self.__ambulatory == 'false') and  (self.__owner_dynamics == 'stably' or self.__owner_dynamics == 'better' or self.__owner_dynamics == 'worse') and (self.__initial == 'true' or self.__initial == 'false') )
            return res
        except TypeError:
            return False
    
    def set_vis_id(self, id : int):
        self.__vis_id = id

    def set_doctor(self, doctor_id : int):
        self.__doctor = doctor_id

    def set_animal(self, animal_id : int):
        self.__animal = animal_id

    def set_ambulatory(self, ambulatory : str):
        self.__ambulatory = ambulatory

    def set_visit_date(self, visit_date : str):
        self.__visit_date = visit_date

    def set_owner_dynamics(self, owner_dynamics : str):
        self.__owner_dynamics = owner_dynamics

    def set_history_disease(self, history_disease : str):
        self.__history_disease = history_disease

    def set_cur_state(self, cur_state : str):
        self.__cur_state = cur_state
    
    def set_diagnosis(self, diagnosis : str):
        self.__diagnosis = diagnosis

    def set_recommendations(self, recommendations : str):
        self.__recommendations = recommendations

    def set_next_visit(self, next_visit : str):
        self.__next_visit = next_visit
    
    def set_prescribings(self, prescribings):
        self.__prescribings = prescribings

    def set_initial(self, initial : str):
        self.__initial = initial

    def set_note(self, note : str):
        self.__note = note

    def get_vis_id(self):
        return self.__vis_id

    def get_doctor(self):
        return self.__doctor

    def get_animal(self):
        return self.__animal

    def get_ambulatory(self):
        return self.__ambulatory

    def get_visit_date(self):
        return self.__visit_date

    def get_owner_dynamics(self):
        return self.__owner_dynamics

    def get_history_disease(self):
        return self.__history_disease

    def get_cur_state(self):
        return self.__cur_state
    
    def get_diagnosis(self):
        return self.__diagnosis

    def get_recommendations(self):
        return self.__recommendations

    def get_next_visit(self):
        return self.__next_visit
    
    def get_prescribings(self):
        return self.__prescribings

    def get_initial(self):
        return self.__initial

    def get_note(self):
        return self.__note
