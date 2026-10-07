
/*
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;


// Methode 1 : sans find()
bool contientSansFind(string mot1, string mot2)
{
    int i = 0;
    int j = 0;

    while (i < mot1.length() && j < mot2.length())
    {
        if (mot1[i] == mot2[j])
        {
            j++;
        }

        i++;
    }

    return j == mot2.length();
}


// Methode 2 : avec find()
bool contientAvecFind(string mot1, string mot2)
{
    int position = 0;

    for (int i = 0; i < mot2.length(); i++)
    {
        position = mot1.find(mot2[i], position);

        if (position == string::npos)
        {
            return false;
        }

        position++;
    }

    return true;
}


int main()
{
    string mot1, mot2;

    cout << "Entrez le premier mot : ";
    cin >> mot1;

    cout << "Entrez le deuxieme mot : ";
    cin >> mot2;


    // Vérification des résultats

    if (contientSansFind(mot1, mot2))
        cout << "Methode 1 : le mot 2 est contenu dans le mot 1." << endl;
    else
        cout << "Methode 1 : le mot 2 n'est pas contenu dans le mot 1." << endl;


    if (contientAvecFind(mot1, mot2))
        cout << "Methode 2 : le mot 2 est contenu dans le mot 1." << endl;
    else
        cout << "Methode 2 : le mot 2 n'est pas contenu dans le mot 1." << endl;


    // Nombre de répétitions
    const int N = 1000000;


    // Mesure du temps de la méthode 1

    auto debut1 = high_resolution_clock::now();

    for (int i = 0; i < N; i++)
    {
        contientSansFind(mot1, mot2);
    }

    auto fin1 = high_resolution_clock::now();

    auto duree1 = duration_cast<nanoseconds>(fin1 - debut1).count();


    // Mesure du temps de la méthode 2

    auto debut2 = high_resolution_clock::now();

    for (int i = 0; i < N; i++)
    {
        contientAvecFind(mot1, mot2);
    }

    auto fin2 = high_resolution_clock::now();

    auto duree2 = duration_cast<nanoseconds>(fin2 - debut2).count();


    // Affichage des résultats

    cout << endl;
    cout << "===== TEMPS D'EXECUTION =====" << endl;

    cout << "Methode 1 (sans find) :" << endl;
    cout << "Temps total : " << duree1 << " ns" << endl;
    cout << "Temps moyen : " << (double)duree1 / N << " ns" << endl;

    cout << endl;

    cout << "Methode 2 (avec find) :" << endl;
    cout << "Temps total : " << duree2 << " ns" << endl;
    cout << "Temps moyen : " << (double)duree2 / N << " ns" << endl;


    return 0;
}
*/
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
