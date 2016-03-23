#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../caryll-sfnt.h"
#include "../caryll-font.h"
#include "../caryll-io.h"

void caryll_read_maxp(caryll_font *font, caryll_packet packet) {
	FOR_TABLE('maxp', table) {
		font_file_pointer data = table.data;
		uint32_t length = table.length;

		if (length != 32 && length != 6) {
			fprintf(stderr, "table 'maxp' corrupted.\n");
			font->maxp = NULL;
		} else {
			table_maxp *maxp = (table_maxp *)malloc(sizeof(table_maxp) * 1);
			maxp->version = caryll_blt32u(data);
			maxp->numGlyphs = caryll_blt16u(data + 4);
			if (maxp->version == 0x00010000) { // TrueType Format 1
				maxp->maxPoints = caryll_blt16u(data + 6);
				maxp->maxContours = caryll_blt16u(data + 8);
				maxp->maxCompositePoints = caryll_blt16u(data + 10);
				maxp->maxCompositeContours = caryll_blt16u(data + 12);
				maxp->maxZones = caryll_blt16u(data + 14);
				maxp->maxTwilightPoints = caryll_blt16u(data + 16);
				maxp->maxStorage = caryll_blt16u(data + 18);
				maxp->maxFunctionDefs = caryll_blt16u(data + 20);
				maxp->maxInstructionDefs = caryll_blt16u(data + 22);
				maxp->maxStackElements = caryll_blt16u(data + 24);
				maxp->maxSizeOfInstructions = caryll_blt16u(data + 26);
				maxp->maxComponentElements = caryll_blt16u(data + 28);
				maxp->maxComponentDepth = caryll_blt16u(data + 30);
			} else { // CFF OTF Format 0.5
				maxp->maxPoints = 0;
				maxp->maxContours = 0;
				maxp->maxCompositePoints = 0;
				maxp->maxCompositeContours = 0;
				maxp->maxZones = 0;
				maxp->maxTwilightPoints = 0;
				maxp->maxStorage = 0;
				maxp->maxFunctionDefs = 0;
				maxp->maxInstructionDefs = 0;
				maxp->maxStackElements = 0;
				maxp->maxSizeOfInstructions = 0;
				maxp->maxComponentElements = 0;
				maxp->maxComponentDepth = 0;
			}
			font->maxp = maxp;
		}
	}
}

void caryll_maxp_to_json(caryll_font *font, json_value *root) {
	if (!font->maxp) return;
	json_value *maxp = json_object_new(15);
	json_object_push(maxp, "version", json_integer_new(font->maxp->version));
	json_object_push(maxp, "numGlyphs", json_integer_new(font->maxp->numGlyphs));
	json_object_push(maxp, "maxPoints", json_integer_new(font->maxp->maxPoints));
	json_object_push(maxp, "maxContours", json_integer_new(font->maxp->maxContours));
	json_object_push(maxp, "maxCompositePoints", json_integer_new(font->maxp->maxCompositePoints));
	json_object_push(maxp, "maxCompositeContours", json_integer_new(font->maxp->maxCompositeContours));
	json_object_push(maxp, "maxZones", json_integer_new(font->maxp->maxZones));
	json_object_push(maxp, "maxTwilightPoints", json_integer_new(font->maxp->maxTwilightPoints));
	json_object_push(maxp, "maxStorage", json_integer_new(font->maxp->maxStorage));
	json_object_push(maxp, "maxFunctionDefs", json_integer_new(font->maxp->maxFunctionDefs));
	json_object_push(maxp, "maxInstructionDefs", json_integer_new(font->maxp->maxInstructionDefs));
	json_object_push(maxp, "maxStackElements", json_integer_new(font->maxp->maxStackElements));
	json_object_push(maxp, "maxSizeOfInstructions", json_integer_new(font->maxp->maxSizeOfInstructions));
	json_object_push(maxp, "maxComponentElements", json_integer_new(font->maxp->maxComponentElements));
	json_object_push(maxp, "maxComponentDepth", json_integer_new(font->maxp->maxComponentDepth));

	json_object_push(root, "maxp", maxp);
}
