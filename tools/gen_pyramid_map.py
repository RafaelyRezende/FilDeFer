#!/usr/bin/env python3
"""Deterministic generator for maps/pyramid.fdf (50x50, 42.fdf-style).

z = clamp(0, center - chebyshev_distance_to_center), so the map is a
square pyramid with a peak height of 24 at the middle of a 50x50 grid.

Usage: python3 tools/gen_pyramid_map.py [output] [size]
"""
import sys


def main():
    out = sys.argv[1] if len(sys.argv) > 1 else "maps/pyramid.fdf"
    n = int(sys.argv[2]) if len(sys.argv) > 2 else 50
    c = (n - 1) / 2.0
    rows = []
    for y in range(n):
        rows.append(" ".join(
            str(int(max(0.0, c - max(abs(x - c), abs(y - c)))))
            for x in range(n)))
    with open(out, "w") as f:
        f.write("\n".join(rows) + "\n")


if __name__ == "__main__":
    main()
