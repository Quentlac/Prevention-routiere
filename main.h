#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
typedef struct{
    GtkWidget* entre_vitesse;

    GSList* liste_etat_conducteur;

    GSList* liste_etat_route;

}Data;

void calcul(GtkWidget* widget, Data* data);

#endif // MAIN_H_INCLUDED
