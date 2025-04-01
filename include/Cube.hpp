#ifndef CUBE_HPP
#define CUBE_HPP

#pragma once

#include <Math.h>

static Math::Vector3f position[] = {
    // -X face
	{-1.f, -1.f, -1.f},
	{-1.f,  1.f, -1.f},
	{-1.f, -1.f,  1.f},
	{-1.f,  1.f,  1.f},

	// +X face
	{ 1.f, -1.f, -1.f},
	{ 1.f,  1.f, -1.f},
	{ 1.f, -1.f,  1.f},
	{ 1.f,  1.f,  1.f},

	// -Y face
	{-1.f, -1.f, -1.f},
	{ 1.f, -1.f, -1.f},
	{-1.f, -1.f,  1.f},
	{ 1.f, -1.f,  1.f},

	// +Y face
	{-1.f,  1.f, -1.f},
	{ 1.f,  1.f, -1.f},
	{-1.f,  1.f,  1.f},
	{ 1.f,  1.f,  1.f},

	// -Z face
	{-1.f, -1.f, -1.f},
	{ 1.f, -1.f, -1.f},
	{-1.f,  1.f, -1.f},
	{ 1.f,  1.f, -1.f},

	// +Z face
	{-1.f, -1.f,  1.f},
	{ 1.f, -1.f,  1.f},
	{-1.f,  1.f,  1.f},
	{ 1.f,  1.f,  1.f}
};

static Math::Vector2f tex_coords[] = {
    // -X face
		{0.f, 0.f},
		{1.f, 0.f},
		{0.f, 1.f},
		{1.f, 1.f},

		// +X face
		{0.f, 0.f},
		{1.f, 0.f},
		{0.f, 1.f},
		{1.f, 1.f},

		// -Y face
		{0.f, 0.f},
		{1.f, 0.f},
		{0.f, 1.f},
		{1.f, 1.f},

	// +Y face
	{0.f, 0.f},
	{1.f, 0.f},
	{0.f, 1.f},
	{1.f, 1.f},

	// -Z face
	{0.f, 0.f},
	{1.f, 0.f},
	{0.f, 1.f},
	{1.f, 1.f},

	// +Z face
	{0.f, 0.f},
	{1.f, 0.f},
	{0.f, 1.f},
	{1.f, 1.f}
};

#endif