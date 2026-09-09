#include "barrel.hpp"

Barrel::Barrel(double total_capacity, double init_alcohol_percent){
    volume = total_capacity;
    alcohol_vol = total_capacity * init_alcohol_percent;
    water_vol = total_capacity * (1.0 - init_alcohol_percent);
}

double Barrel::get_alc_concentration(){
    if (not volume) return 0.0;
    return alcohol_vol / volume;
}

void Barrel::pour_from(Barrel &sourse){
    double cup = sourse.amount / sourse.volume;

    double alc_cup = cup * sourse.alcohol_vol;
    double wat_cup = cup * sourse.water_vol;

    sourse.alcohol_vol -= alc_cup;
    sourse.water_vol -= wat_cup;
    sourse.volume -= amount;

    this->alcohol_vol += alc_cup;
    this->water_vol += wat_cup;
    this->volume += amount;
}