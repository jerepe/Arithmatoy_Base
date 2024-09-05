# Maths 2600 - Représentation et formalisation des nombres

Ce repository de code accompagne la première session de cours de mathématiques de [l'école de cybersécurité 2600](https://candidature.ecole2600.com/).

Les slides de cours sont disponible ici: https://c2ba-learning.gitlab.io/maths/maths-2600-slides-nombres/1

## Exercices de TP

Plusieurs exercices sont à réaliser pendant le cours / TP et seront notés.

Ces exercices en python sont à réaliser dans `tests/tp.py`. Le fichier `tests/test_tp.py` contient des tests automatiques qui seront utilisés pour vous noter, et ne doit pas être modifié.

Il est interdit d'utiliser des `import` dans le fichier `tests/tp.py`, tout votre code doit être from scratch.

Pour mettre en place votre environnement de développement python:

- Créez un environnement virtuel python: `python -m venv .venv`
- Activez le:
  - `source .venv/bin/activate` sous Linux / Mac
  - `source .venv/scripts/activate` sous Windows
- Installez `pytest` dans le venv: `python -m pip install pytest`
- Executez les tests de TP: `python -m pytest tests/test_tp.py`

Ces tests doivent échouer la première fois, et passer une fois votre implémentation terminée.

Vous pouvez lancer un seul test du fichier avec la commande `python -m pytest tests/test_tp.py -k NOM_DU_TEST`.

Dans l'ordre des exercices à faire en TP:

```bash
python -m pytest tests/test_tp.py -k test_nombre_entier
python -m pytest tests/test_tp.py -k test_successeur
python -m pytest tests/test_tp.py -k test_addition
python -m pytest tests/test_tp.py -k test_multiplication
python -m pytest tests/test_tp.py -k test_facto_ite
python -m pytest tests/test_tp.py -k test_facto_rec
python -m pytest tests/test_tp.py -k test_fibo_rec
python -m pytest tests/test_tp.py -k test_fibo_ite
python -m pytest tests/test_tp.py -k test_golden_phi
python -m pytest tests/test_tp.py -k test_sqrt5
python -m pytest tests/test_tp.py -k test_pow
```

Pour débugguer vous pouvez mettre des `print` dans vos tests et lancer avec l'option `-s`, par exemple: `python -m pytest tests/test_tp.py -k test_nombre_entier -s`

Vous pouvez également lancer python en interactif sur le fichier: `python -im tests.tp`. Vous pouvez alors appeler vos fonctions.

Pour une meilleure experience interactive, vous pouvez également installer `ipython` sur votre système, le lancer puis utiliser la commande `%run tests/tp.py` pour charger/recharger votre script et appeler ses fonctions interactivement.

## Projet - Arithmatoy

### Sujet

L'objectif de ce projet est d'implémenter en C les algorithmes d'addition, soustraction et multiplication vu à l'école primaire.

L'implémentation doit fonctionner dans n'importe quelle base de 2 à 36, utilisant les chiffres parmis: `0123456789abcdefghijklmnopqrstuvwxyz`. Par exemple, le nombre 35 peut s'écrire:

- `35` en base 10
- `100011` en base 2
- `23` en base 16 (hexadécimal)
- `z` en base 36
- `10` en base 35

Votre objectif est d'implémenter les fonction `arithmatoy_add`, `arithmatoy_sub` et `arithmatoy_mul` définies dans [arithmatoy.c](src/arithmatoy.c).

A l'issue de votre implémentation, l'ensemble des tests du projet doivent passer.

Plusieurs fonctions utilitaires vous sont données pour faciliter l'implémentation.

**Attention**: Vous devez implémenter les algorithmes directement sur les chaines de caractère d'entrée des fonctions, pas convertir ces chaines en nombre pour faire le calcul. En particulier vos fonctions doivent gérer des nombres arbitrairement grands.

En plus de cela, si la variable `VERBOSE` vaut `1`, il faudra afficher des logs sur stderr indiquant les étapes intermédiaires des calculs (opérations sur chiffres et retenues). Les logs à afficher doivent avoir le même format que ceux que vous trouverez dans les fichiers sous [`tests/outputs/`](tests/outputs). Ces fichiers ont été généré avec mon implémentation et vous pouvez utiliser les tests de non regression python du projet pour valider que votre programme produit les même logs.

### Mise en place

Vous aurez besoin à minima de CMake et un compilateur C. La configuration conseillée est gcc sous Linux/Mac, Visual Studio sous Windows, mais vous êtes libre d'adapter à votre cas d'utilisation. Le projet est configuré pour l'editeur Visual Studio Code pour tout ce qui est configuration de debug et formattage automatique.

- Sourcez le script bash: `source .devenv/bash_init.sh`. Ce fichier contient des commandes bash utilitaires.
- Lancez la commande `setup`. Cette commande va installer [`vcpkg`](https://vcpkg.io/en/index.html), compiler la lib de test [`cmocka`](https://cmocka.org/), et lancer `cmake`.
- Compilez en debug: `cmake_build_debug`
- Lancez les tests en debug: `ctest_debug`

Les tests devraient échouer, vous devez implémenter les fonctions pour les faire passer.

### Lancer les tests de non regression python

Ces tests lancent `arithmatoy-cli`, l'application en ligne de commande compilée par le projet. Le but des tests est de comparer l'output de votre programme avec des outputs de référence.

- Lancez la commande `cmake_install_debug`. Cette commande va compiler et installer des fichiers dans `.local/cmake/dist`.
- Si ce n'est pas déjà fait, installez l'environnement de dev python comme expliqué pour les exercices de TP
- Executez pytest: `python -m pytest tests/test_arithmatoy.py`

Ces tests peuvent être assez long à executer et devraient également échouer, vous devez implémenter les fonctions pour les faire passer. Cela implique d'implémenter le logging de manière à matcher mes outputs. Referrez vous aux fichiers de reference stockés dans [`tests/outputs/`](tests/outputs) pour observer et reproduire le format des logs.

Vous pouvez lancer la commande `python -m pytest --force-regen` pour forcer le re-création des fichiers de sortie à partir de votre implémentation, et comparer les différences dans une UI affichant les diff Git.
