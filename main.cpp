#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;


// =====================================================
// Méthode 1 : sans find()
// Recherche d'une sous-chaîne CONSECUTIVE
// =====================================================

bool contientSansFind(string mot, string sousChaine)
{
    // Si la sous-chaîne est plus longue que le mot
    if (sousChaine.length() > mot.length())
    {
        return false;
    }

    // On teste chaque position possible
    for (int i = 0; i <= mot.length() - sousChaine.length(); i++)
    {
        bool identique = true;

        // Comparer les caractères consécutifs
        for (int j = 0; j < sousChaine.length(); j++)
        {
            if (mot[i + j] != sousChaine[j])
            {
                identique = false;
                break;
            }
        }

        // Toute la sous-chaîne a été trouvée
        if (identique)
        {
            return true;
        }
    }

    return false;
}


// =====================================================
// Méthode 2 : avec find()
// Recherche d'une sous-chaîne CONSECUTIVE
// =====================================================

bool contientAvecFind(string mot, string sousChaine)
{
    return mot.find(sousChaine) != string::npos;
}


// =====================================================
// Méthode 3 : remplacement SANS find()
// =====================================================

string remplacerSansFind(string mot, string ancienne, string nouvelle)
{
    string resultat = "";

    int i = 0;

    while (i < mot.length())
    {
        bool identique = true;

        // Vérifier si l'ancienne sous-chaîne
        // commence à la position i
        if (i + ancienne.length() <= mot.length())
        {
            for (int j = 0; j < ancienne.length(); j++)
            {
                if (mot[i + j] != ancienne[j])
                {
                    identique = false;
                    break;
                }
            }
        }
        else
        {
            identique = false;
        }

        // Si l'ancienne sous-chaîne est trouvée
        if (identique)
        {
            // Ajouter la nouvelle sous-chaîne
            resultat += nouvelle;

            // Sauter l'ancienne sous-chaîne
            i += ancienne.length();
        }
        else
        {
            // Copier le caractère actuel
            resultat += mot[i];

            i++;
        }
    }

    return resultat;
}


// =====================================================
// Programme principal
// =====================================================

int main()
{
    vector<string> mots;

    string mot;
    string sousChaine;
    string nouvelleSousChaine;


    // =================================================
    // Ouvrir le fichier
    // =================================================

    ifstream fichier("fichier.txt");

    if (!fichier)
    {
        cout << "Erreur d'ouverture du fichier." << endl;
        return 1;
    }


    // =================================================
    // Lire les mots du fichier
    // =================================================

    while (fichier >> mot)
    {
        mots.push_back(mot);
    }

    fichier.close();


    // =================================================
    // Demander la sous-chaîne à rechercher
    // =================================================

    cout << "Entrez la sous-chaine a rechercher : ";
    cin >> sousChaine;


    // =================================================
    // METHODE 1 : SANS FIND()
    // =================================================

    auto debut1 = high_resolution_clock::now();

    int nombre1 = 0;

    for (int i = 0; i < mots.size(); i++)
    {
        if (contientSansFind(mots[i], sousChaine))
        {
            nombre1++;
        }
    }

    auto fin1 = high_resolution_clock::now();

    double temps1 =
        duration<double, milli>(fin1 - debut1).count();


    // =================================================
    // METHODE 2 : AVEC FIND()
    // =================================================

    auto debut2 = high_resolution_clock::now();

    int nombre2 = 0;

    for (int i = 0; i < mots.size(); i++)
    {
        if (contientAvecFind(mots[i], sousChaine))
        {
            nombre2++;
        }
    }

    auto fin2 = high_resolution_clock::now();

    double temps2 =
        duration<double, milli>(fin2 - debut2).count();


    // =================================================
    // AFFICHAGE DES RESULTATS DE RECHERCHE
    // =================================================

    cout << endl;
    cout << "========== RESULTATS DE RECHERCHE =========="
         << endl;

    cout << "Sous-chaine recherchee : "
         << sousChaine << endl;

    cout << endl;

    cout << "Methode 1 : nombre de mots contenant \""
         << sousChaine
         << "\" consecutivement : "
         << nombre1 << endl;

    cout << "Temps methode 1 (sans find) : "
         << temps1 << " ms" << endl;

    cout << endl;

    cout << "Methode 2 : nombre de mots contenant \""
         << sousChaine
         << "\" consecutivement : "
         << nombre2 << endl;

    cout << "Temps methode 2 (avec find) : "
         << temps2 << " ms" << endl;


    // =================================================
    // DEMANDER LA NOUVELLE SOUS-CHAINE
    // =================================================

    cout << endl;

    cout << "Entrez la nouvelle sous-chaine : ";
    cin >> nouvelleSousChaine;


    // =================================================
    // REMPLACEMENT DANS LE VECTOR
    // SANS MODIFIER LE FICHIER
    // =================================================

    auto debut3 = high_resolution_clock::now();

    int nombreRemplacements = 0;

    // Vector contenant seulement quelques exemples
    vector<string> exemples;

    for (int i = 0; i < mots.size(); i++)
    {
        // Garder l'ancien mot
        string ancienMot = mots[i];

        // Effectuer le remplacement
        mots[i] = remplacerSansFind(
            mots[i],
            sousChaine,
            nouvelleSousChaine
        );

        // Vérifier si le mot a été modifié
        if (ancienMot != mots[i])
        {
            nombreRemplacements++;

            // Garder seulement les 10 premiers exemples
            if (exemples.size() < 10)
            {
                exemples.push_back(
                    ancienMot + " -> " + mots[i]
                );
            }
        }
    }

    auto fin3 = high_resolution_clock::now();

    double temps3 =
        duration<double, milli>(fin3 - debut3).count();


    // =================================================
    // AFFICHAGE DU REMPLACEMENT
    // =================================================

    cout << endl;
    cout << "========== REMPLACEMENT =========="
         << endl;

    cout << "Ancienne sous-chaine : "
         << sousChaine << endl;

    cout << "Nouvelle sous-chaine : "
         << nouvelleSousChaine << endl;

    cout << "Nombre total de mots modifies : "
         << nombreRemplacements << endl;

    cout << endl;

    cout << "Quelques exemples de remplacement :"
         << endl;

    for (int i = 0; i < exemples.size(); i++)
    {
        cout << exemples[i] << endl;
    }

    cout << endl;

    cout << "Temps de remplacement : "
         << temps3 << " ms" << endl;


    return 0;
}
