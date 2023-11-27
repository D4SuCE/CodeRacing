#pragma once

#include "types.h"

class RaceTrack
{
public:
    CoordsVertex firstLine = {
        { 265, 182 },
        { 265, 181 },
        { 264, 181 },
        { 263, 180 },
        { 261, 180 },
        { 259, 179 },
        { 255, 179 },
        { 251, 179 },
        { 250, 179 },
        { 245, 179 },
        { 244, 179 },
        { 239, 179 },
        { 232, 179 },
        { 226, 179 },
        { 221, 179 },
        { 215, 179 },
        { 211, 179 },
        { 206, 179 },
        { 201, 179 },
        { 196, 179 },
        { 191, 180 },
        { 186, 182 },
        { 182, 184 },
        { 178, 187 },
        { 175, 189 },
        { 172, 192 },
        { 168, 196 },
        { 165, 200 },
        { 162, 205 },
        { 159, 210 },
        { 158, 216 },
        { 157, 220 },
        { 157, 225 },
        { 158, 229 },
        { 159, 233 },
        { 160, 237 },
        { 163, 241 },
        { 167, 245 },
        { 171, 249 },
        { 176, 253 },
        { 181, 257 },
        { 187, 260 },
        { 193, 263 },
        { 201, 265 },
        { 211, 267 },
        { 223, 269 },
        { 235, 270 },
        { 250, 272 },
        { 264, 272 },
        { 277, 272 },
        { 289, 272 },
        { 301, 270 },
        { 312, 268 },
        { 322, 266 },
        { 330, 263 },
        { 338, 259 },
        { 344, 256 },
        { 349, 252 },
        { 352, 248 },
        { 355, 243 },
        { 357, 238 },
        { 359, 233 },
        { 359, 229 },
        { 359, 225 },
        { 359, 221 },
        { 359, 217 },
        { 358, 213 },
        { 357, 209 },
        { 354, 205 },
        { 352, 202 },
        { 349, 199 },
        { 347, 197 },
        { 344, 195 },
        { 341, 192 },
        { 339, 191 },
        { 335, 189 },
        { 332, 187 },
        { 328, 186 },
        { 325, 184 },
        { 321, 183 },
        { 317, 182 },
        { 313, 181 },
        { 309, 180 },
        { 305, 180 },
        { 300, 179 },
        { 297, 179 },
        { 294, 179 },
        { 290, 179 },
        { 287, 179 },
        { 283, 179 },
        { 280, 179 },
        { 278, 179 },
        { 277, 179 },
        { 275, 179 },
        { 274, 179 },
        { 273, 179 },
        { 272, 179 },
        { 271, 179 },
        { 270, 179 }
    };
    CoordsVertex secondLine = {
        { 266, 150 },
        { 265, 149 },
        { 261, 147 },
        { 256, 146 },
        { 249, 145 },
        { 240, 143 },
        { 229, 142 },
        { 218, 142 },
        { 207, 142 },
        { 196, 142 },
        { 187, 142 },
        { 179, 143 },
        { 171, 145 },
        { 163, 148 },
        { 155, 150 },
        { 147, 154 },
        { 140, 159 },
        { 133, 163 },
        { 126, 167 },
        { 126, 168 },
        { 121, 172 },
        { 117, 177 },
        { 112, 183 },
        { 110, 188 },
        { 108, 194 },
        { 106, 200 },
        { 105, 207 },
        { 105, 214 },
        { 105, 220 },
        { 105, 227 },
        { 107, 232 },
        { 110, 239 },
        { 114, 245 },
        { 118, 251 },
        { 123, 256 },
        { 128, 262 },
        { 134, 267 },
        { 141, 273 },
        { 150, 278 },
        { 161, 286 },
        { 174, 293 },
        { 187, 298 },
        { 201, 303 },
        { 217, 308 },
        { 234, 311 },
        { 252, 314 },
        { 271, 316 },
        { 289, 318 },
        { 309, 318 },
        { 329, 318 },
        { 349, 318 },
        { 370, 316 },
        { 388, 312 },
        { 404, 309 },
        { 418, 305 },
        { 429, 300 },
        { 439, 294 },
        { 446, 287 },
        { 453, 280 },
        { 459, 272 },
        { 464, 263 },
        { 468, 254 },
        { 471, 246 },
        { 473, 238 },
        { 475, 231 },
        { 476, 224 },
        { 476, 217 },
        { 475, 211 },
        { 473, 205 },
        { 473, 204 },
        { 470, 198 },
        { 467, 192 },
        { 463, 186 },
        { 458, 180 },
        { 452, 175 },
        { 444, 168 },
        { 436, 163 },
        { 428, 158 },
        { 421, 154 },
        { 413, 150 },
        { 407, 147 },
        { 399, 144 },
        { 392, 142 },
        { 384, 139 },
        { 377, 137 },
        { 369, 136 },
        { 362, 134 },
        { 356, 134 },
        { 351, 133 },
        { 344, 133 },
        { 338, 133 },
        { 332, 133 },
        { 326, 133 },
        { 320, 133 },
        { 315, 134 },
        { 311, 135 },
        { 306, 136 },
        { 302, 137 },
        { 298, 138 },
        { 296, 139 },
        { 293, 140 },
        { 290, 141 },
        { 288, 142 },
        { 286, 142 },
        { 285, 143 },
        { 284, 143 },
        { 283, 143 },
        { 282, 144 },
        { 281, 144 },
        { 280, 145 },
        { 279, 145 },
        { 278, 145 },
        { 276, 146 },
        { 275, 146 },
        { 274, 146 },
        { 273, 147 },
        { 272, 147 },
        { 271, 147 },
        { 270, 147 },
        { 269, 148 },
        { 268, 148 }
    };
    CoordsChain firstLineChain;
    CoordsChain secondLineChain;

public:
    RaceTrack() {
        firstLineChain = createCoordsChain(firstLine);
        secondLineChain = createCoordsChain(secondLine);
    }


private:
    CoordsChain createCoordsChain(const CoordsVertex& firstLine) {
        CoordsChain chain;
        CoordsPair pair;
        for (size_t i = 0; i < firstLine.size() - 1; ++i) {
            pair = { firstLine[i], firstLine[i + 1] };
            chain.push_back(pair);
        }
        return chain;
    }
};
