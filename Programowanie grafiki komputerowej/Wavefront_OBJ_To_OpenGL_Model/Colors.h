#pragma once

////////////////////////////////////////////////////////////////////////////////////
/*
    RGB color definitions in ASP.NET.
*/
////////////////////////////////////////////////////////////////////////////////////

// _________________________________________________________________________________

#include <GL/gl.h>

// _________________________________________________________________________________

const unsigned short int COLOR_SIZE = 4;

const GLfloat ALICE_BLUE              [ COLOR_SIZE ] = { (GLfloat)0.941176, (GLfloat)0.972549, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat ANTIQUE_WHITE           [ COLOR_SIZE ] = { (GLfloat)0.980392, (GLfloat)0.921569, (GLfloat)0.843137, (GLfloat)1.000000 };
const GLfloat AQUA                    [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat AQUAMARINE              [ COLOR_SIZE ] = { (GLfloat)0.498039, (GLfloat)1.000000, (GLfloat)0.831373, (GLfloat)1.000000 };
const GLfloat AZURE                   [ COLOR_SIZE ] = { (GLfloat)0.941176, (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat BEIGE                   [ COLOR_SIZE ] = { (GLfloat)0.960784, (GLfloat)0.960784, (GLfloat)0.862745, (GLfloat)1.000000 };
const GLfloat BISQUE                  [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.894118, (GLfloat)0.768627, (GLfloat)1.000000 };
const GLfloat BLACK                   [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat BLANCHED_ALMOND         [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.921569, (GLfloat)0.803922, (GLfloat)1.000000 };
const GLfloat BLUE                    [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat BLUE_VIOLET             [ COLOR_SIZE ] = { (GLfloat)0.541176, (GLfloat)0.168627, (GLfloat)0.886275, (GLfloat)1.000000 };
const GLfloat BROWN                   [ COLOR_SIZE ] = { (GLfloat)0.647059, (GLfloat)0.164706, (GLfloat)0.164706, (GLfloat)1.000000 };
const GLfloat BURLY_WOOD              [ COLOR_SIZE ] = { (GLfloat)0.870588, (GLfloat)0.721569, (GLfloat)0.529412, (GLfloat)1.000000 };
const GLfloat CADET_BLUE              [ COLOR_SIZE ] = { (GLfloat)0.372549, (GLfloat)0.619608, (GLfloat)0.627451, (GLfloat)1.000000 };
const GLfloat CHARTREUSE              [ COLOR_SIZE ] = { (GLfloat)0.498039, (GLfloat)1.000000, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat CHOCOLATE               [ COLOR_SIZE ] = { (GLfloat)0.823529, (GLfloat)0.411765, (GLfloat)0.117647, (GLfloat)1.000000 };
const GLfloat CORAL                   [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.498039, (GLfloat)0.313725, (GLfloat)1.000000 };
const GLfloat CORNFLOWER_BLUE         [ COLOR_SIZE ] = { (GLfloat)0.392157, (GLfloat)0.584314, (GLfloat)0.929412, (GLfloat)1.000000 };
const GLfloat CORNSILK                [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.972549, (GLfloat)0.862745, (GLfloat)1.000000 };
const GLfloat CRIMSON                 [ COLOR_SIZE ] = { (GLfloat)0.862745, (GLfloat)0.078431, (GLfloat)0.235294, (GLfloat)1.000000 };
const GLfloat CYAN                    [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat DARK_BLUE               [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)0.545098, (GLfloat)1.000000 };
const GLfloat DARK_CYAN               [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.545098, (GLfloat)0.545098, (GLfloat)1.000000 };
const GLfloat DARK_GOLDENROD          [ COLOR_SIZE ] = { (GLfloat)0.721569, (GLfloat)0.525490, (GLfloat)0.043137, (GLfloat)1.000000 };
const GLfloat DARK_GRAY               [ COLOR_SIZE ] = { (GLfloat)0.662745, (GLfloat)0.662745, (GLfloat)0.662745, (GLfloat)1.000000 };
const GLfloat DARK_GREEN              [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.392157, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat DARK_KHAKI              [ COLOR_SIZE ] = { (GLfloat)0.741176, (GLfloat)0.717647, (GLfloat)0.419608, (GLfloat)1.000000 };
const GLfloat DARK_MAGENTA            [ COLOR_SIZE ] = { (GLfloat)0.545098, (GLfloat)0.000000, (GLfloat)0.545098, (GLfloat)1.000000 };
const GLfloat DARK_OLIVE_GREEN        [ COLOR_SIZE ] = { (GLfloat)0.333333, (GLfloat)0.419608, (GLfloat)0.184314, (GLfloat)1.000000 };
const GLfloat DARK_ORANGE             [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.549020, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat DARK_ORCHID             [ COLOR_SIZE ] = { (GLfloat)0.600000, (GLfloat)0.196078, (GLfloat)0.800000, (GLfloat)1.000000 };
const GLfloat DARK_RED                [ COLOR_SIZE ] = { (GLfloat)0.545098, (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat DARK_SALMON             [ COLOR_SIZE ] = { (GLfloat)0.913725, (GLfloat)0.588235, (GLfloat)0.478431, (GLfloat)1.000000 };
const GLfloat DARK_SEA_GREEN          [ COLOR_SIZE ] = { (GLfloat)0.560784, (GLfloat)0.737255, (GLfloat)0.545098, (GLfloat)1.000000 };
const GLfloat DARK_SLATE_BLUE         [ COLOR_SIZE ] = { (GLfloat)0.282353, (GLfloat)0.239216, (GLfloat)0.545098, (GLfloat)1.000000 };
const GLfloat DARK_SLATE_GRAY         [ COLOR_SIZE ] = { (GLfloat)0.184314, (GLfloat)0.309804, (GLfloat)0.309804, (GLfloat)1.000000 };
const GLfloat DARK_TURQUOISE          [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.807843, (GLfloat)0.819608, (GLfloat)1.000000 };
const GLfloat DARK_VIOLET             [ COLOR_SIZE ] = { (GLfloat)0.580392, (GLfloat)0.000000, (GLfloat)0.827451, (GLfloat)1.000000 };
const GLfloat DEEP_PINK               [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.078431, (GLfloat)0.576471, (GLfloat)1.000000 };
const GLfloat DEEP_SKY_BLUE           [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.749020, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat DIM_GRAY                [ COLOR_SIZE ] = { (GLfloat)0.411765, (GLfloat)0.411765, (GLfloat)0.411765, (GLfloat)1.000000 };
const GLfloat DODGER_BLUE             [ COLOR_SIZE ] = { (GLfloat)0.117647, (GLfloat)0.564706, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat FIREBRICK               [ COLOR_SIZE ] = { (GLfloat)0.698039, (GLfloat)0.133333, (GLfloat)0.133333, (GLfloat)1.000000 };
const GLfloat FLORAL_WHITE            [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.980392, (GLfloat)0.941176, (GLfloat)1.000000 };
const GLfloat FOREST_GREEN            [ COLOR_SIZE ] = { (GLfloat)0.133333, (GLfloat)0.545098, (GLfloat)0.133333, (GLfloat)1.000000 };
const GLfloat FUCHSIA                 [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat GAINSBORO               [ COLOR_SIZE ] = { (GLfloat)0.862745, (GLfloat)0.862745, (GLfloat)0.862745, (GLfloat)1.000000 };
const GLfloat GHOST_WHITE             [ COLOR_SIZE ] = { (GLfloat)0.972549, (GLfloat)0.972549, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat GOLD                    [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.843137, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat GOLDENROD               [ COLOR_SIZE ] = { (GLfloat)0.854902, (GLfloat)0.647059, (GLfloat)0.125490, (GLfloat)1.000000 };
const GLfloat GRAY                    [ COLOR_SIZE ] = { (GLfloat)0.501961, (GLfloat)0.501961, (GLfloat)0.501961, (GLfloat)1.000000 };
const GLfloat GREEN                   [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.501961, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat GREEN_YELLOW            [ COLOR_SIZE ] = { (GLfloat)0.678431, (GLfloat)1.000000, (GLfloat)0.184314, (GLfloat)1.000000 };
const GLfloat HONEYDEW                [ COLOR_SIZE ] = { (GLfloat)0.941176, (GLfloat)1.000000, (GLfloat)0.941176, (GLfloat)1.000000 };
const GLfloat HOT_PINK                [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.411765, (GLfloat)0.705882, (GLfloat)1.000000 };
const GLfloat INDIAN_RED              [ COLOR_SIZE ] = { (GLfloat)0.803922, (GLfloat)0.360784, (GLfloat)0.360784, (GLfloat)1.000000 };
const GLfloat INDIGO                  [ COLOR_SIZE ] = { (GLfloat)0.294118, (GLfloat)0.000000, (GLfloat)0.509804, (GLfloat)1.000000 };
const GLfloat IVORY                   [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)0.941176, (GLfloat)1.000000 };
const GLfloat KHAKI                   [ COLOR_SIZE ] = { (GLfloat)0.941176, (GLfloat)0.901961, (GLfloat)0.549020, (GLfloat)1.000000 };
const GLfloat LAVENDER                [ COLOR_SIZE ] = { (GLfloat)0.901961, (GLfloat)0.901961, (GLfloat)0.980392, (GLfloat)1.000000 };
const GLfloat LAVENDER_BLUSH          [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.941176, (GLfloat)0.960784, (GLfloat)1.000000 };
const GLfloat LAWN_GREEN              [ COLOR_SIZE ] = { (GLfloat)0.486275, (GLfloat)0.988235, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat LEMON_CHIFFON           [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.980392, (GLfloat)0.803922, (GLfloat)1.000000 };
const GLfloat LIGHT_BLUE              [ COLOR_SIZE ] = { (GLfloat)0.678431, (GLfloat)0.847059, (GLfloat)0.901961, (GLfloat)1.000000 };
const GLfloat LIGHT_CORAL             [ COLOR_SIZE ] = { (GLfloat)0.941176, (GLfloat)0.501961, (GLfloat)0.501961, (GLfloat)1.000000 };
const GLfloat LIGHT_CYAN              [ COLOR_SIZE ] = { (GLfloat)0.878431, (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat LIGHT_GOLDENROD_YELLOW  [ COLOR_SIZE ] = { (GLfloat)0.980392, (GLfloat)0.980392, (GLfloat)0.823529, (GLfloat)1.000000 };
const GLfloat LIGHT_GRAY              [ COLOR_SIZE ] = { (GLfloat)0.827451, (GLfloat)0.827451, (GLfloat)0.827451, (GLfloat)1.000000 };
const GLfloat LIGHT_GREEN             [ COLOR_SIZE ] = { (GLfloat)0.564706, (GLfloat)0.933333, (GLfloat)0.564706, (GLfloat)1.000000 };
const GLfloat LIGHT_PINK              [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.713725, (GLfloat)0.756863, (GLfloat)1.000000 };
const GLfloat LIGHT_SALMON            [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.627451, (GLfloat)0.478431, (GLfloat)1.000000 };
const GLfloat LIGHT_SEA_GREEN         [ COLOR_SIZE ] = { (GLfloat)0.125490, (GLfloat)0.698039, (GLfloat)0.666667, (GLfloat)1.000000 };
const GLfloat LIGHT_SKY_BLUE          [ COLOR_SIZE ] = { (GLfloat)0.529412, (GLfloat)0.807843, (GLfloat)0.980392, (GLfloat)1.000000 };
const GLfloat LIGHT_SLATE_GRAY        [ COLOR_SIZE ] = { (GLfloat)0.466667, (GLfloat)0.533333, (GLfloat)0.600000, (GLfloat)1.000000 };
const GLfloat LIGHT_STEEL_BLUE        [ COLOR_SIZE ] = { (GLfloat)0.690196, (GLfloat)0.768627, (GLfloat)0.870588, (GLfloat)1.000000 };
const GLfloat LIGHT_YELLOW            [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)0.878431, (GLfloat)1.000000 };
const GLfloat LIME                    [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)1.000000, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat LIME_GREEN              [ COLOR_SIZE ] = { (GLfloat)0.196078, (GLfloat)0.803922, (GLfloat)0.196078, (GLfloat)1.000000 };
const GLfloat LINEN                   [ COLOR_SIZE ] = { (GLfloat)0.980392, (GLfloat)0.941176, (GLfloat)0.901961, (GLfloat)1.000000 };
const GLfloat MAGENTA                 [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat MAROON                  [ COLOR_SIZE ] = { (GLfloat)0.501961, (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat MEDIUM_AQUAMARINE       [ COLOR_SIZE ] = { (GLfloat)0.400000, (GLfloat)0.803922, (GLfloat)0.666667, (GLfloat)1.000000 };
const GLfloat MEDIUM_BLUE             [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)0.803922, (GLfloat)1.000000 };
const GLfloat MEDIUM_ORCHID           [ COLOR_SIZE ] = { (GLfloat)0.729412, (GLfloat)0.333333, (GLfloat)0.827451, (GLfloat)1.000000 };
const GLfloat MEDIUM_PURPLE           [ COLOR_SIZE ] = { (GLfloat)0.576471, (GLfloat)0.439216, (GLfloat)0.858824, (GLfloat)1.000000 };
const GLfloat MEDIUM_SEA_GREEN        [ COLOR_SIZE ] = { (GLfloat)0.235294, (GLfloat)0.701961, (GLfloat)0.443137, (GLfloat)1.000000 };
const GLfloat MEDIUM_SLATE_BLUE       [ COLOR_SIZE ] = { (GLfloat)0.482353, (GLfloat)0.407843, (GLfloat)0.933333, (GLfloat)1.000000 };
const GLfloat MEDIUM_SPRING_GREEN     [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.980392, (GLfloat)0.603922, (GLfloat)1.000000 };
const GLfloat MEDIUM_TURQUOISE        [ COLOR_SIZE ] = { (GLfloat)0.282353, (GLfloat)0.819608, (GLfloat)0.800000, (GLfloat)1.000000 };
const GLfloat MEDIUM_VIOLET_RED       [ COLOR_SIZE ] = { (GLfloat)0.780392, (GLfloat)0.082353, (GLfloat)0.521569, (GLfloat)1.000000 };
const GLfloat MIDNIGHT_BLUE           [ COLOR_SIZE ] = { (GLfloat)0.098039, (GLfloat)0.098039, (GLfloat)0.439216, (GLfloat)1.000000 };
const GLfloat MINT_CREAM              [ COLOR_SIZE ] = { (GLfloat)0.960784, (GLfloat)1.000000, (GLfloat)0.980392, (GLfloat)1.000000 };
const GLfloat MISTY_ROSE              [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.894118, (GLfloat)0.882353, (GLfloat)1.000000 };
const GLfloat MOCCASIN                [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.894118, (GLfloat)0.709804, (GLfloat)1.000000 };
const GLfloat NAVAJO_WHITE            [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.870588, (GLfloat)0.678431, (GLfloat)1.000000 };
const GLfloat NAVY                    [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)0.501961, (GLfloat)1.000000 };
const GLfloat OLD_LACE                [ COLOR_SIZE ] = { (GLfloat)0.992157, (GLfloat)0.960784, (GLfloat)0.901961, (GLfloat)1.000000 };
const GLfloat OLIVE                   [ COLOR_SIZE ] = { (GLfloat)0.501961, (GLfloat)0.501961, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat OLIVE_DRAB              [ COLOR_SIZE ] = { (GLfloat)0.419608, (GLfloat)0.556863, (GLfloat)0.137255, (GLfloat)1.000000 };
const GLfloat ORANGE                  [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.647059, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat ORANGE_RED              [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.270588, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat ORCHID                  [ COLOR_SIZE ] = { (GLfloat)0.854902, (GLfloat)0.439216, (GLfloat)0.839216, (GLfloat)1.000000 };
const GLfloat PALE_GOLDENROD          [ COLOR_SIZE ] = { (GLfloat)0.933333, (GLfloat)0.909804, (GLfloat)0.666667, (GLfloat)1.000000 };
const GLfloat PALE_GREEN              [ COLOR_SIZE ] = { (GLfloat)0.596078, (GLfloat)0.984314, (GLfloat)0.596078, (GLfloat)1.000000 };
const GLfloat PALE_TURQUOISE          [ COLOR_SIZE ] = { (GLfloat)0.686275, (GLfloat)0.933333, (GLfloat)0.933333, (GLfloat)1.000000 };
const GLfloat PALE_VIOLET_RED         [ COLOR_SIZE ] = { (GLfloat)0.858824, (GLfloat)0.439216, (GLfloat)0.576471, (GLfloat)1.000000 };
const GLfloat PAPAYA_WHIP             [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.937255, (GLfloat)0.835294, (GLfloat)1.000000 };
const GLfloat PEACH_PUFF              [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.854902, (GLfloat)0.725490, (GLfloat)1.000000 };
const GLfloat PERU                    [ COLOR_SIZE ] = { (GLfloat)0.803922, (GLfloat)0.521569, (GLfloat)0.247059, (GLfloat)1.000000 };
const GLfloat PINK                    [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.752941, (GLfloat)0.796078, (GLfloat)1.000000 };
const GLfloat PLUM                    [ COLOR_SIZE ] = { (GLfloat)0.866667, (GLfloat)0.627451, (GLfloat)0.866667, (GLfloat)1.000000 };
const GLfloat POWDER_BLUE             [ COLOR_SIZE ] = { (GLfloat)0.690196, (GLfloat)0.878431, (GLfloat)0.901961, (GLfloat)1.000000 };
const GLfloat PURPLE                  [ COLOR_SIZE ] = { (GLfloat)0.501961, (GLfloat)0.000000, (GLfloat)0.501961, (GLfloat)1.000000 };
const GLfloat RED                     [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.000000, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat ROSY_BROWN              [ COLOR_SIZE ] = { (GLfloat)0.737255, (GLfloat)0.560784, (GLfloat)0.560784, (GLfloat)1.000000 };
const GLfloat ROYAL_BLUE              [ COLOR_SIZE ] = { (GLfloat)0.254902, (GLfloat)0.411765, (GLfloat)0.882353, (GLfloat)1.000000 };
const GLfloat SADDLE_BROWN            [ COLOR_SIZE ] = { (GLfloat)0.545098, (GLfloat)0.270588, (GLfloat)0.074510, (GLfloat)1.000000 };
const GLfloat SALMON                  [ COLOR_SIZE ] = { (GLfloat)0.980392, (GLfloat)0.501961, (GLfloat)0.447059, (GLfloat)1.000000 };
const GLfloat SANDY_BROWN             [ COLOR_SIZE ] = { (GLfloat)0.956863, (GLfloat)0.643137, (GLfloat)0.376471, (GLfloat)1.000000 };
const GLfloat SEA_GREEN               [ COLOR_SIZE ] = { (GLfloat)0.180392, (GLfloat)0.545098, (GLfloat)0.341176, (GLfloat)1.000000 };
const GLfloat SEA_SHELL               [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.960784, (GLfloat)0.933333, (GLfloat)1.000000 };
const GLfloat SIENNA                  [ COLOR_SIZE ] = { (GLfloat)0.627451, (GLfloat)0.321569, (GLfloat)0.176471, (GLfloat)1.000000 };
const GLfloat SILVER                  [ COLOR_SIZE ] = { (GLfloat)0.752941, (GLfloat)0.752941, (GLfloat)0.752941, (GLfloat)1.000000 };
const GLfloat SKY_BLUE                [ COLOR_SIZE ] = { (GLfloat)0.529412, (GLfloat)0.807843, (GLfloat)0.921569, (GLfloat)1.000000 };
const GLfloat SLATE_BLUE              [ COLOR_SIZE ] = { (GLfloat)0.415686, (GLfloat)0.352941, (GLfloat)0.803922, (GLfloat)1.000000 };
const GLfloat SLATE_GRAY              [ COLOR_SIZE ] = { (GLfloat)0.439216, (GLfloat)0.501961, (GLfloat)0.564706, (GLfloat)1.000000 };
const GLfloat SNOW                    [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.980392, (GLfloat)0.980392, (GLfloat)1.000000 };
const GLfloat SPRING_GREEN            [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)1.000000, (GLfloat)0.498039, (GLfloat)1.000000 };
const GLfloat STEEL_BLUE              [ COLOR_SIZE ] = { (GLfloat)0.274510, (GLfloat)0.509804, (GLfloat)0.705882, (GLfloat)1.000000 };
const GLfloat TAN                     [ COLOR_SIZE ] = { (GLfloat)0.823529, (GLfloat)0.705882, (GLfloat)0.549020, (GLfloat)1.000000 };
const GLfloat TEAL                    [ COLOR_SIZE ] = { (GLfloat)0.000000, (GLfloat)0.501961, (GLfloat)0.501961, (GLfloat)1.000000 };
const GLfloat THISTLE                 [ COLOR_SIZE ] = { (GLfloat)0.847059, (GLfloat)0.749020, (GLfloat)0.847059, (GLfloat)1.000000 };
const GLfloat TOMATO                  [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)0.388235, (GLfloat)0.278431, (GLfloat)1.000000 };
const GLfloat TRANSPARENT_COLOR       [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat TURQUOISE               [ COLOR_SIZE ] = { (GLfloat)0.250980, (GLfloat)0.878431, (GLfloat)0.815686, (GLfloat)1.000000 };
const GLfloat VIOLET                  [ COLOR_SIZE ] = { (GLfloat)0.933333, (GLfloat)0.509804, (GLfloat)0.933333, (GLfloat)1.000000 };
const GLfloat WHEAT                   [ COLOR_SIZE ] = { (GLfloat)0.960784, (GLfloat)0.870588, (GLfloat)0.701961, (GLfloat)1.000000 };
const GLfloat WHITE                   [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)1.000000 };
const GLfloat WHITE_SMOKE             [ COLOR_SIZE ] = { (GLfloat)0.960784, (GLfloat)0.960784, (GLfloat)0.960784, (GLfloat)1.000000 };
const GLfloat YELLOW                  [ COLOR_SIZE ] = { (GLfloat)1.000000, (GLfloat)1.000000, (GLfloat)0.000000, (GLfloat)1.000000 };
const GLfloat YELLOW_GREEN            [ COLOR_SIZE ] = { (GLfloat)0.603922, (GLfloat)0.803922, (GLfloat)0.196078, (GLfloat)1.000000 };
