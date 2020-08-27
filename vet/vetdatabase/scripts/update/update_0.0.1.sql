---- add constraint

ALTER TABLE clients ADD CONSTRAINT addr_client_fk 
    FOREIGN KEY (address) REFERENCES addresses(addr_id) 
    ON DELETE CASCADE;

ALTER TABLE clients ADD CONSTRAINT pass_client_fk 
    FOREIGN KEY (passport) REFERENCES passports(pass_id) 
    ON DELETE CASCADE;

ALTER TABLE staff ADD CONSTRAINT pass_staff_fk 
    FOREIGN KEY (passport) REFERENCES passports(pass_id) 
    ON DELETE CASCADE;

ALTER TABLE staff ADD CONSTRAINT pos_staff_fk 
    FOREIGN KEY (position) REFERENCES position(pos_id) 
    ON DELETE CASCADE;

ALTER TABLE access ADD CONSTRAINT stf_empl_fk 
    FOREIGN KEY (employee) REFERENCES staff(staff_id) 
    ON DELETE CASCADE;

ALTER TABLE contract ADD CONSTRAINT own_cntr_fk 
    FOREIGN KEY ("owner") REFERENCES clients(cli_id) 
    ON DELETE CASCADE;

ALTER TABLE schedule ADD CONSTRAINT empl_schdl_fk 
    FOREIGN KEY (employee_id) REFERENCES staff(staff_id) 
    ON DELETE CASCADE;

ALTER TABLE animals_medical_records ADD CONSTRAINT anmr_ctrc_fk 
    FOREIGN KEY (contract) REFERENCES contract(contr_id) 
    ON DELETE CASCADE;

ALTER TABLE animals_medical_records ADD CONSTRAINT anmr_mchp_fk 
    FOREIGN KEY (chip_id) REFERENCES microchips(chip_id) 
    ON DELETE CASCADE;

ALTER TABLE visits ADD CONSTRAINT vis_schdl_fk 
    FOREIGN KEY (doctor) REFERENCES staff(staff_id) 
    ON DELETE CASCADE;

ALTER TABLE visits ADD CONSTRAINT vis_anmr_fk 
    FOREIGN KEY (animal) REFERENCES animals_medical_records(anim_id) 
    ON DELETE CASCADE;

ALTER TABLE visits ADD CONSTRAINT vsts_asts_fk 
    FOREIGN KEY (cur_state) REFERENCES animal_states(state_id) 
    ON DELETE CASCADE;

ALTER TABLE passports ADD CONSTRAINT unique_pass_num UNIQUE(num);

ALTER TABLE microchips ADD CONSTRAINT unique_mchip_num UNIQUE(chip_num);
