#ifndef GUARD_OAM_SLICER_H
#define GUARD_OAM_SLICER_H
#include "../gfx.h"
#include <stdbool.h>

enum OamShapeEnum {
    OAM_SQUARE = 0,
    OAM_H_RECTANGLE = 1,
    OAM_V_RECTANGLE = 2
};

enum OamSizeEnum {
    OAM_SIZE_3 = 3,
    OAM_SIZE_2 = 2,
    OAM_SIZE_1 = 1,
    OAM_SIZE_0 = 0
};

typedef struct OamShape {
    unsigned short width;
    unsigned short height;
    enum OamSizeEnum oamSize;
    enum OamShapeEnum mode;
} OamShape;

typedef struct OamOverrideSegment {
    unsigned short offX;
    unsigned short offY;
    unsigned short width;
    unsigned short height;
    bool spacer;
} OamOverrideSegment;

typedef struct OamOverride {
    unsigned short width;
    unsigned short height;
    unsigned short numSegments;
    const struct OamOverrideSegment *segments;
} OamOverride;

typedef struct OamSegment {
    struct OamSegment *next;
    short offX;
    short offY;
    unsigned short width;  // in tiles
    unsigned short height; // in tiles
    bool spacer; // indicates this segment represents a spacer (no tile data)
} OamSegment;

void print_oam_segments(struct OamSegment *segList);
void free_oam_segments(struct OamSegment *segList);
int getOamTileIndex(int width, int height, TileCoord *tileCoordinates);
// Extended variant: provide an explicit sequence of segments (optional).
// If sequence==NULL, behaves like getOamTileIndex.
// Extended variant: fills `tileCoordinates` with the full ordering (including spacer positions).
// If `sequence==NULL` behaves like getOamTileIndex. If `outSpacerMask` is non-NULL it will be filled
// with `width*height` boolean entries marking which positions are spacers.
int getOamTileIndexEx(int width, int height, TileCoord *tileCoordinates, const OamOverrideSegment *sequence, int numSequenceSegments, struct OamSegment **outSegments);

// Validate whether a WxH tile piece is a valid OAM shape
bool is_valid_oam_shape(int width, int height);
void PrintTileCoords(TileCoord *tileSequence, int tile_count);

#endif // GUARD_OAM_SLICER_H