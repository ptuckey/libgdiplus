/*
 * Copyright © 2008 Chris Wilson
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of
 * Chris Wilson not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission. Chris Wilson makes no representations about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * CHRIS WILSON DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL CHRIS WILSON BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author: Chris Wilson <chris@chris-wilson.co.uk>
 */

#include "cairo-test.h"

static cairo_test_draw_function_t draw;

cairo_test_t test = {
    "smask-fill",
    "Test the support of \"soft\" masks with fills",
    60, 60,
    draw
};

static cairo_test_status_t
draw (cairo_t *cr, int width, int height)
{
    cairo_surface_t *mask;
    cairo_pattern_t *pattern;
    cairo_t *cr2;

    mask = cairo_surface_create_similar (cairo_get_group_target (cr),
				         CAIRO_CONTENT_ALPHA,
					 width, height);
    cr2 = cairo_create (mask);

    cairo_save (cr2); {
	cairo_set_operator (cr2, CAIRO_OPERATOR_CLEAR);
	cairo_paint (cr2);
    } cairo_restore (cr2);

    pattern = cairo_pattern_create_linear (0, 0, width, height);
    cairo_pattern_add_color_stop_rgba (pattern, 0.00, 0., 0., 0., 0.);
    cairo_pattern_add_color_stop_rgba (pattern, 0.25, 1., 1., 1., 1.);
    cairo_pattern_add_color_stop_rgba (pattern, 0.50, 1., 1., 1., .5);
    cairo_pattern_add_color_stop_rgba (pattern, 0.75, 1., 1., 1., 1.);
    cairo_pattern_add_color_stop_rgba (pattern, 1.00, 0., 0., 0., 0.);
    cairo_set_source (cr2, pattern);
    cairo_pattern_destroy (pattern);

    cairo_arc (cr2, 0.5 * width, 0.5 * height, 0.45 * height, 0, 2 * M_PI);
    cairo_fill (cr2);
    cairo_destroy (cr2);


    cairo_set_source_rgb (cr, 0, 0, 1.0);
    cairo_paint (cr);

    cairo_set_source_rgb (cr, 1.0, 0, 0);
    cairo_mask_surface (cr, mask, 0, 0);
    cairo_surface_destroy (mask);

    return CAIRO_TEST_SUCCESS;
}

int
main (void)
{
    return cairo_test (&test);
}

