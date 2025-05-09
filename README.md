# Simulation de Colonies de Termites 🐜

## Contexte et Objectif 🎯

Ce projet est une **simulation de colonies de termites** en compétition pour créer un nid en rassemblant des brindilles. En utilisant un algorithme **décentralisé et auto-stabilisant**, il permet d’observer comment des agents simples interagissent pour donner naissance à un système complexe. Le comportement des fourmis à de plus était adapté afin d'améliorer la réalité et le dynamisme de leur mouvement( déplacement de manière reflechi, attaque et rammassage de brindilles de manère dynamique etc...)

La simulation repose sur la **stigmergie**, un mode de communication indirect où les termites influencent leur environnement en modifiant leur disposition des brindilles.

## Fonctionnalités 🛠️

- **Déplacement aléatoire des termites** sur une grille en 2D.
- **Ramassage et dépôt de brindilles** pour former un seul gros tas.
- **Gestion du temps** avec une période d’attente avant de déposer une brindille.
- **Mécanismes de blocage et déblocage** des termites en fonction de l’environnement.
- **Possibilité d’ajouter plusieurs colonies de termites** avec des stratégies différentes.
- **Affichage dynamique** dans le terminal avec des caractères ASCII et utilisation possible des couleurs ANSI.
- **Gestion avancée des nids** : chaque termite peut marquer ses brindilles et ne ramasser que celles de son nid ou de l’adversaire.

## Développement 🏗️

### 1. Modélisation et Implémentation
- **Grille 2D** représentant l’environnement des termites.
- **Agents termites** avec des comportements spécifiques (déplacement, ramassage, dépôt).
- **Paramètres modifiables** pour observer différentes stratégies d’optimisation.
- **Utilisation de constantes** pour ajuster la probabilité de tourner et la durée avant dépôt.

### 2. Algorithme de Simulation
1. **Marche aléatoire** du termite.
2. **Ramassage d’une brindille**.
3. **Recherche d’un tas existant**.
4. **Dépôt de la brindille sur un tas**.

La simulation fonctionne **de manière itérative**, avec un déplacement simultané de tous les termites.

### 3. Gestion des Nids (Extension)
- Possibilité d’avoir **plusieurs colonies concurrentes**.
- Chaque termite peut marquer ses brindilles avec une signature de son nid.
- Une colonie est déclarée gagnante lorsqu’elle possède le plus de brindilles marquées.

## Installation 🚀

1. **Cloner le dépôt** :
   ```bash
   git clone https://github.com/Ismaelwn/Termites.git
   ```

## Contribution 🤝

Les contributions sont encouragées !
1. **Forker le dépôt** 📌
2. **Créer une branche** (`git checkout -b feature/nouvelle_fonctionnalité`)
3. **Committer vos modifications** (`git commit -m "Ajout d’un mode de simulation avancé"`)
4. **Pousser votre branche** (`git push origin feature/nouvelle_fonctionnalité`)
5. **Ouvrir une Pull Request** 📬


