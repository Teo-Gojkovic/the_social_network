# 📡 Projet Client-Serveur UDP avec Chiffrement de César

## 📝 Description
Ce projet consiste en deux programmes en langage C : un **client** et un **serveur**. Ces programmes communiquent entre eux via le protocole UDP. Les messages échangés sont chiffrés et déchiffrés à l'aide du **chiffrement de César**, un algorithme simple de cryptographie par décalage.

## 🗂️ Structure du projet
```
.
├── client_cesar.c
├── serveur_cesar.c
└── README.md
```

* `client_cesar.c` : Code source du programme client.
* `serveur_cesar.c` : Code source du programme serveur.
* `README.md` : Documentation du projet.

## ⚙️ Compilation
Utilisez le compilateur `gcc` pour compiler les programmes.

### Compilation du serveur
```bash
gcc -o serveur_cesar serveur_cesar.c
```

### Compilation du client
```bash
gcc -o client_cesar client_cesar.c
```

## 🚀 Exécution

### Lancer le serveur
```bash
./serveur_cesar
```
Le serveur sera en attente de messages sur le port **12345**.

### Lancer le client
```bash
./client_cesar
```
Le client enverra des messages au serveur à l'adresse IP **127.0.0.1** sur le port **12345**.

## 🔐 Chiffrement de César
Le chiffrement de César est un algorithme de substitution simple qui consiste à décaler chaque caractère d'un message d'un certain nombre de positions dans l'alphabet.

Dans ce projet, le décalage utilisé est de **3** positions.

### Exemple
* Message original : `Bonjour`
* Message chiffré : `Erqmrxu`

Le chiffrement et le déchiffrement sont gérés par des fonctions dédiées dans le code source.

## 📌 Remarques
* Le port utilisé pour la communication est **12345**. Vous pouvez le modifier dans les fichiers source si nécessaire.
* Assurez-vous que le port choisi est ouvert sur votre pare-feu pour permettre la communication entre le client et le serveur.
* Le programme est conçu pour une utilisation en local (localhost). Pour une utilisation sur un réseau, adaptez l'adresse IP en conséquence.

## 📚 Ressources supplémentaires
* [Documentation sur le protocole UDP](https://fr.wikipedia.org/wiki/User_Datagram_Protocol)
* [Explication du chiffrement de César](https://fr.wikipedia.org/wiki/Chiffrement_par_d%C3%A9calage)