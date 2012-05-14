#include <glib.h>
#include <gio/gio.h>

int
main(int argc, char **argv)
{
	GDBusProxy *player_proxy;
	GError *err = NULL;
	GVariant *ret, *value;
	GVariantIter iter;
	gchar *key;

	g_type_init();

	/*                                   connection,         flags,                   info, name,                            object_path,                     interface_name,                  cancellable,               error) */
	player_proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, NULL, "org.mpris.MediaPlayer2.rhythmbox", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player", NULL, &err);

	g_clear_error(&err);
	/*
	if (g_dbus_proxy_call_sync(player_proxy, "Next", NULL, G_DBUS_CALL_FLAGS_NONE, -1, NULL, &err) == NULL)
	{
		g_print("Meh: %s\n", err->message);
	}
	*/
	ret = g_dbus_proxy_get_cached_property(player_proxy, "Metadata");
	g_variant_iter_init(&iter, ret);
	while (g_variant_iter_next(&iter, "{sv}", &key, &value))
	{
		if (g_ascii_strcasecmp("xesam:title", key) == 0)
		{
			g_print("Title: %s\n", g_variant_get_string(value, NULL));
		}
		if (g_ascii_strcasecmp("xesam:artist", key) == 0)
		{
			const gchar **artist;
			gsize alen, i;

			g_print("Artist info:\n");
			artist = g_variant_get_strv(value, &alen);
			for (i = 0; i < alen; i++)
			{
				g_print("\t%s\n", artist[i]);
			}
		}
		if (g_ascii_strcasecmp("xesam:album", key) == 0)
		{
			g_print("Album: %s\n", g_variant_get_string(value, NULL));
		}

		//g_print("'%s' is of type %s\n", key, g_variant_get_type_string(value));
	}
	g_variant_unref(value);
	return 0;
}

