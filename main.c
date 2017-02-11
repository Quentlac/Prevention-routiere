#include <stdlib.h>
#include <gtk/gtk.h>
#include "main.h"

int main (int argc, char *argv[])
{

    Data data;
    gtk_init(&argc, &argv);
    GtkWidget * fenetre = NULL;
    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetre),"Distance arret");
    gtk_window_set_default_size(GTK_WINDOW(fenetre),100,100);

    //creation de la box principal vertical
    GtkWidget * formu = NULL;
    formu = gtk_vbox_new(TRUE,6);

    //creation d'un titre
    GtkWidget * titre = NULL;
    titre = gtk_label_new("<big><b><u>Distance d'arret</u></b></big>");
    gtk_label_set_use_markup(GTK_LABEL(titre),TRUE);
    gtk_box_pack_start(GTK_BOX(formu),titre,FALSE,FALSE,0);

    //ajout d'un parametre(vitesse)
    //ajout d'une boite horizontal:
    GtkWidget* hbox = NULL;
    hbox=gtk_hbox_new(TRUE,0);

    //ajout d'un texte:
    GtkWidget* texte_vitesse = NULL;
    texte_vitesse = gtk_label_new("<b>Vitesse: </b>");
    gtk_label_set_use_markup(GTK_LABEL(texte_vitesse),TRUE);
    gtk_box_pack_start(GTK_BOX(hbox),texte_vitesse,FALSE,FALSE,0);

    //ajout de l'entré:
    data.entre_vitesse = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox),data.entre_vitesse,FALSE,FALSE,0);

    //ajout de l'unite
    GtkWidget* unit_vitesse = NULL;
    unit_vitesse = gtk_label_new("<b> Km/h</b>");
    gtk_label_set_use_markup(GTK_LABEL(unit_vitesse),TRUE);
    gtk_box_pack_start(GTK_BOX(hbox),unit_vitesse,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(formu),hbox,FALSE,FALSE,0);

    //ajout d'une nouvelle entré(etat conducteur)
    //ajout d'un texte
    GtkWidget* texte_tmpreact = NULL;
    texte_tmpreact = gtk_label_new("<b><u>Etat conducteur</u></b>");
    gtk_label_set_use_markup(GTK_LABEL(texte_tmpreact),TRUE);
    gtk_box_pack_start(GTK_BOX(formu),texte_tmpreact,FALSE,FALSE,0);

    /*GtkWidget* position_tmp = NULL;
    position_tmp = gtk_fixed_new();*/

    //creation d'une boite horizontal
    GtkWidget* hbox2 = NULL;
    hbox2 = gtk_hbox_new(TRUE,0);

    GtkWidget* tmpreaction1 = NULL;
    GtkWidget* tmpreaction2 = NULL;
    GtkWidget* tmpreaction3 = NULL;

    tmpreaction1 = gtk_radio_button_new_with_label(NULL,"En plein forme");
    data.liste_etat_conducteur = gtk_radio_button_get_group(tmpreaction1);
    gtk_box_pack_start(GTK_BOX(hbox2),tmpreaction1,FALSE,FALSE,0);


    tmpreaction2 = gtk_radio_button_new_with_label(data.liste_etat_conducteur,"Un peu fatigue");
    data.liste_etat_conducteur = gtk_radio_button_get_group(tmpreaction2);
    gtk_box_pack_start(GTK_BOX(hbox2),tmpreaction2,FALSE,FALSE,0);

    tmpreaction3 = gtk_radio_button_new_with_label(data.liste_etat_conducteur,"Fatigue");
    data.liste_etat_conducteur = gtk_radio_button_get_group(tmpreaction3);
    gtk_box_pack_start(GTK_BOX(hbox2),tmpreaction3,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(formu),hbox2,FALSE,FALSE,0);

    //ajout d'une nouvelle entré(etat route)
    //ajout de l'etiquette
    GtkWidget* texte_etatroute = NULL;
    texte_etatroute = gtk_label_new("<b><u>Etat route</u></b>");
    gtk_label_set_use_markup(GTK_LABEL(texte_etatroute),TRUE);
    gtk_box_pack_start(GTK_BOX(formu),texte_etatroute,FALSE,FALSE,0);

    //ajout d'une boite horizonatal
    GtkWidget* hbox3 = NULL;
    hbox3 = gtk_hbox_new(TRUE,0);

    //ajout des boutons radio
    GtkWidget* etat_route1 = NULL;
    GtkWidget* etat_route2 = NULL;

    etat_route1 = gtk_radio_button_new_with_label(NULL,"Sec");
    data.liste_etat_route = gtk_radio_button_get_group(etat_route1);
    gtk_box_pack_start(GTK_BOX(hbox3),etat_route1,FALSE,FALSE,0);

    etat_route2 = gtk_radio_button_new_with_label(data.liste_etat_route,"Mouille");
    data.liste_etat_route = gtk_radio_button_get_group(etat_route2);
    gtk_box_pack_start(GTK_BOX(hbox3),etat_route2,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(formu),hbox3,FALSE,FALSE,0);

    //ajout d'un bouton de validation:
    GtkWidget* bouton = NULL;
    bouton = gtk_button_new_with_label("Calculer");
    gtk_box_pack_start(GTK_BOX(formu),bouton,FALSE,FALSE,0);
    g_signal_connect(G_OBJECT(bouton),"clicked",G_CALLBACK(calcul),(gpointer) &data);



    gtk_container_add(GTK_WINDOW(fenetre),GTK_BOX(formu));
    gtk_widget_show_all(fenetre);
    gtk_signal_connect(G_OBJECT(fenetre),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_main();
    return(0);
}

void calcul(GtkWidget* widget, Data* data){
    GtkWidget* fenetre = NULL;
    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetre),"Resultat du calcul");
    gtk_window_set_default_size(GTK_WINDOW(fenetre),400,200);
    //recuperation des donnes
    char* entre_vitesse = gtk_entry_get_text(GTK_ENTRY(data->entre_vitesse));

    //recuperation des radios(reaction)
    GSList* liste_bt_tmp_react = data->liste_etat_conducteur;

    char* nom_label_select_react;

    while(liste_bt_tmp_react){
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(liste_bt_tmp_react->data))){
            nom_label_select_react = gtk_button_get_label(GTK_BUTTON(liste_bt_tmp_react->data));

            liste_bt_tmp_react = NULL;

        }
        else{
            liste_bt_tmp_react= g_slist_next(liste_bt_tmp_react);

        }

    }


    //recuperation des radios(etat route)
    GSList* liste_bt_etat_route = data->liste_etat_route;

    char* nom_label_select_route;

    while(liste_bt_etat_route){
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(liste_bt_etat_route->data))){
            nom_label_select_route = gtk_button_get_label(GTK_BUTTON(liste_bt_etat_route->data));

            liste_bt_etat_route = NULL;

        }
        else{
            liste_bt_etat_route= g_slist_next(liste_bt_etat_route);

        }

    }

    //conversion du label en dist_reaction(tmp_reaction)
    //calcul de la distance de reaction
    double dist_reaction = 0;
    //conversion de la chaine entre vitesse en nombre
    int vitesse = atoi(entre_vitesse);

    if(strcmp(nom_label_select_react,"En plein forme") == 0){
        dist_reaction = 5/18.0*vitesse;
    }
    if(strcmp(nom_label_select_react,"Un peu fatigue") == 0){
        dist_reaction = 5/13.5*vitesse;
    }
    if(strcmp(nom_label_select_react,"Fatigue") == 0){
        dist_reaction = 5/9.0*vitesse;
    }

    //conversion du label(route)
    double etat_route = 0;

    if(strcmp(nom_label_select_route,"Sec") == 0){
        etat_route = 0.8;
    }
    if(strcmp(nom_label_select_route,"Mouille") == 0){
        etat_route = 0.4;
    }


    float dist_freinage = 0;
    float dist_total = 0;


    //calcul de la distance de freinage:
    dist_freinage = (vitesse*vitesse)/(254.0*etat_route);

    //calcul de la distance d'arret total:
    dist_total = dist_reaction + dist_freinage;


    //on transforme les resulat en chaine de caractere:
    char result_dist_reaction[1000];
    sprintf(result_dist_reaction,"<b>Distance de reaction:</b> %f <b>m</b>",dist_reaction);


    char result_dist_freinage[1000];
    sprintf(result_dist_freinage,"<b>Distance de freinage:</b> %f <b>m</b>",dist_freinage);

    char result_dist_total[1000];
    sprintf(result_dist_total,"<b>Distance d'arret total:</b> %f <b>m</b>",dist_total);

    printf("%s",result_dist_total);

    //ajout des donnés dans une fenetre

    //creation d'une boite vertical

    GtkWidget* resultat = NULL;
    resultat = gtk_vbox_new(TRUE,0);

    //creation d'un label(dist_reaction)
    GtkWidget* label_dist_react = NULL;
    label_dist_react= gtk_label_new(result_dist_reaction);
    gtk_label_set_use_markup(GTK_LABEL(label_dist_react),TRUE);
    gtk_box_pack_start(GTK_BOX(resultat),label_dist_react,FALSE,FALSE,0);

    //creation d'un autre label(dist freinage)
    GtkWidget* label_dist_frein = NULL;
    label_dist_frein = gtk_label_new(result_dist_freinage);
    gtk_label_set_use_markup(GTK_LABEL(label_dist_frein),TRUE);
    gtk_box_pack_start(GTK_BOX(resultat),label_dist_frein,FALSE,FALSE,0);

    //creation d'un autre label(dist total)
    GtkWidget* label_dist_total = NULL;
    label_dist_total = gtk_label_new(result_dist_total);
    gtk_label_set_use_markup(GTK_LABEL(label_dist_total),TRUE);
    gtk_box_pack_start(GTK_BOX(resultat),label_dist_total,FALSE,FALSE,0);

    //ajout d'une image
    GtkWidget* image = NULL;
    image = gtk_image_new_from_file("./image.png");
    gtk_box_pack_start(GTK_BOX(resultat),image,FALSE,FALSE,0);

    gtk_container_add(GTK_WINDOW(fenetre),GTK_BOX(resultat));
    gtk_widget_show_all(fenetre);
    g_signal_connect(G_OBJECT(fenetre),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_main();





}
