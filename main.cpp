#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;


// =====================================================
// M�thode 1 : sans find()
// Recherche d'une sous-cha�ne CONSECUTIVE
// =====================================================

bool contientSansFind(string mot, string sousChaine)
{
    // Si la sous-cha�ne est plus longue que le mot
    if (sousChaine.length() > mot.length())
    {
        return false;
    }

    // On teste chaque position possible
    for (int i = 0; i <= mot.length() - sousChaine.length(); i++)
    {
        bool identique = true;

        // Comparer les caract�res cons�cutifs
        for (int j = 0; j < sousChaine.length(); j++)
        {
            if (mot[i + j] != sousChaine[j])
            {
                identique = false;
                break;
            }
        }

        // Toute la sous-cha�ne a �t� trouv�e
        if (identique)
        {
            return true;
        }
    }

    return false;
}


// =====================================================
// M�thode 2 : avec find()
// Recherche d'une sous-cha�ne CONSECUTIVE
// =====================================================

bool contientAvecFind(string mot, string sousChaine)
{
    return mot.find(sousChaine) != string::npos;
}


// =====================================================
// M�thode 3 : remplacement SANS find()
// =====================================================

string remplacerSansFind(string mot, string ancienne, string nouvelle)
{
    string resultat = "";

    int i = 0;

    while (i < mot.length())
    {
        bool identique = true;

        // V�rifier si l'ancienne sous-cha�ne
        // commence � la position i
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

        // Si l'ancienne sous-cha�ne est trouv�e
        if (identique)
        {
            // Ajouter la nouvelle sous-cha�ne
            resultat += nouvelle;

            // Sauter l'ancienne sous-cha�ne
            i += ancienne.length();
        }
        else
        {
            // Copier le caract�re actuel
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
    // Demander la sous-cha�ne � rechercher
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

    for (int i = 0; i < mots.size(); i++)
    {
        mots[i] = remplacerSansFind(
            mots[i],
            sousChaine,
            nouvelleSousChaine
        );
    }

    auto fin3 = high_resolution_clock::now();

    double temps3 =
        duration<double, milli>(fin3 - debut3).count();


    // =================================================
    // AFFICHAGE DU TEMPS DE REMPLACEMENT
    // =================================================

    cout << endl;
    cout << "========== REMPLACEMENT =========="
         << endl;

    cout << "Ancienne sous-chaine : "
         << sousChaine << endl;

    cout << "Nouvelle sous-chaine : "
         << nouvelleSousChaine << endl;

    cout << "Temps de remplacement : "
         << temps3 << " ms" << endl;


    // =================================================
    // AFFICHER QUELQUES MOTS APRES REMPLACEMENT
    // =================================================

    cout << endl;
    cout << "========== MOTS APRES REMPLACEMENT =========="
         << endl;

    for (int i = 0; i < mots.size(); i++)
    {
        cout << mots[i] << endl;
    }


    return 0;
}
