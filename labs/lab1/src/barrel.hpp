class Barrel{
    private:
        double volume;
        double alcohol_vol;
        double water_vol;
        double amount = 1.0; 

    public:

    Barrel(double total_capacity, double init_alcohol_percent);

    void pour_from(Barrel &sourse);

    double get_alc_concentration();
};
