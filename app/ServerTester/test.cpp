#include <SFML/Graphics.h>

int main() {
    // Création de la fenêtre
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Ma fenetre", sfResize | sfClose, NULL);

    // Boucle principale
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }

        // Efface la fenêtre avec une couleur spécifique (bleu clair dans cet exemple)
        sfColor backgroundColor = sfColor_fromRGB(173, 216, 230); // Couleur bleu clair (RGB)
        sfRenderWindow_clear(window, backgroundColor);

        // Dessinez vos éléments ici

        // Affiche le contenu de la fenêtre
        sfRenderWindow_display(window);
    }

    // Libère les ressources
    sfRenderWindow_destroy(window);

    return 0;
}
