/* EvalWindow.c: Expression evaluation window
 * Copyright 2015, 2016 Vincent Damewood
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "StringSource.h"
#include "InfixParser.h"
#include "Value.h"

#if !defined GLADEDIR
#error "You must define GLADEDIR to build this file."
#endif

static void Calculate(GtkWidget *Widget, gpointer EvalWindow)
{
	SilikoSyntaxTreeNode *ResultTree =
		SilikoParseInfix(
		SilikoStringSourceNew(
		gtk_entry_get_text(
		GTK_ENTRY(
		gtk_builder_get_object(GTK_BUILDER(EvalWindow), "Input")))));
	SilikoValue Value = SilikoSyntaxTreeEvaluate(ResultTree);
	SilikoSyntaxTreeDelete(ResultTree);

	char *ResultString = SilikoValueToString(Value);
	gtk_label_set_text(
		GTK_LABEL(
			gtk_builder_get_object(
			GTK_BUILDER(EvalWindow), "Output")),
		ResultString);
	free(ResultString);
}

GtkBuilder *EvalWindowNew(void)
{
	GtkBuilder *EvalWindow = gtk_builder_new();

	GError *error = NULL;
	if (!gtk_builder_add_from_file(EvalWindow, GLADEDIR "/EvalWindow.glade", &error))
	{
		g_warning("Couldn't load builder file: %s", error->message);
		g_error_free(error);
		return EvalWindow;
	}

	g_signal_connect(
		gtk_builder_get_object(EvalWindow, "EvalWindow"),
		"delete_event",
		G_CALLBACK(gtk_main_quit),
		NULL);
	g_signal_connect(
		gtk_builder_get_object(EvalWindow, "CalculateButton"),
		"clicked",
		G_CALLBACK(Calculate),
		EvalWindow);
	g_signal_connect(
		gtk_builder_get_object(EvalWindow, "Input"),
		"activate",
		G_CALLBACK(Calculate),
		EvalWindow);

	return EvalWindow;
}
