#include <poppler.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    PopplerDocument *doc;
    GError *err = NULL;
    gchar *absolute_file_name = g_strdup_printf("file://%s", argv[1]);

    doc = poppler_document_new_from_file (absolute_file_name, NULL, &err);
    g_free(absolute_file_name);
    if (doc == NULL) {
        g_print ("Could not create PopplerDocument\n");
        if (err != NULL) {
            g_print ("Error: %s\n", err->message);
            g_error_free (err);
        }
        return 1;
    }

    int n_pages = poppler_document_get_n_pages (doc);
    for (int i = 0; i < n_pages; i++) {
        PopplerPage *page = poppler_document_get_page (doc, i);
        if (page) {
            gchar *text = poppler_page_get_text (page);
            g_print ("%s", text);
            g_free (text);
            g_object_unref (page);
        }
    }

    g_object_unref (doc);
    return 0;
}
