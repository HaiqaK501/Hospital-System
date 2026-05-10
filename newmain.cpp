#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <ctime>


static float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
float clamp01(float x)
{
    return x < 0 ? 0 : x>1 ? 1 : x;
}

// ─── NEW: draw a spiral DNA-helix tendril ribbon ────────────────────────────
void drawDNAHelix(sf::RenderWindow& w, float cx, float cy, float T, float alpha)
{
    const int STEPS = 80;
    float height = 300.f;
    for (int i = 0; i < STEPS - 1; i++) {
        float t1 = float(i) / STEPS;
        float t2 = float(i + 1) / STEPS;
        float y1 = cy - height * 0.5f + t1 * height;
        float y2 = cy - height * 0.5f + t2 * height;
        float ang1 = t1 * 6.28f * 2.5f + T * 0.7f;
        float ang2 = t2 * 6.28f * 2.5f + T * 0.7f;
        float x1a = cx + std::cos(ang1) * 22.f;
        float x2a = cx + std::cos(ang2) * 22.f;
        float x1b = cx - std::cos(ang1) * 22.f;
        float x2b = cx - std::cos(ang2) * 22.f;
        // strand A
        sf::Vertex la[2];
        la[0].position = { x1a, y1 };
        la[1].position = { x2a, y2 };
        uint8_t aa = uint8_t(alpha * (0.3f + 0.4f * std::abs(std::cos(ang1))));
        la[0].color = { 0, 210, 230, aa };
        la[1].color = { 0, 180, 210, aa };
        w.draw(la, 2, sf::PrimitiveType::Lines);
        // strand B
        sf::Vertex lb[2];
        lb[0].position = { x1b, y1 };
        lb[1].position = { x2b, y2 };
        lb[0].color = { 0, 160, 200, aa };
        lb[1].color = { 0, 130, 180, aa };
        w.draw(lb, 2, sf::PrimitiveType::Lines);
        // rungs
        if (i % 6 == 0) {
            sf::Vertex rung[2];
            rung[0].position = { x1a, y1 };
            rung[1].position = { x1b, y1 };
            uint8_t ra = uint8_t(alpha * 0.25f);
            rung[0].color = { 100, 230, 255, ra };
            rung[1].color = { 100, 230, 255, ra };
            w.draw(rung, 2, sf::PrimitiveType::Lines);
        }
    }
}

// ─── NEW: draw aurora wave bands across the background ──────────────────────
void drawAuroraWaves(sf::RenderWindow& w, float W, float H, float T, float alpha)
{
    const int BANDS = 5;
    float offsets[BANDS] = { 0.25f, 0.40f, 0.55f, 0.68f, 0.80f };
    float speeds[BANDS] = { 0.18f, 0.22f, 0.14f, 0.26f, 0.10f };
    float amps[BANDS] = { 18.f,  24.f,  14.f,  20.f,  12.f };
    uint8_t alphas[BANDS] = { 5,     7,     4,     6,     3 };
    uint8_t rs[BANDS] = { 0,     0,    20,     0,    10 };
    uint8_t gs[BANDS] = { 160, 200,   180,   220,   160 };
    uint8_t bs[BANDS] = { 230, 200,   255,   190,   240 };

    const int SEG = 80;
    for (int b = 0; b < BANDS; b++) {
        float baseY = H * offsets[b];
        uint8_t a = uint8_t(alphas[b] * alpha / 255.f);
        for (int i = 0; i < SEG - 1; i++) {
            float x1 = W * float(i) / SEG;
            float x2 = W * float(i + 1) / SEG;
            float y1 = baseY + std::sin(x1 / W * 6.28f * 1.5f + T * speeds[b]) * amps[b];
            float y2 = baseY + std::sin(x2 / W * 6.28f * 1.5f + T * speeds[b]) * amps[b];
            sf::Vertex line[2];
            line[0].position = { x1, y1 };
            line[1].position = { x2, y2 };
            line[0].color = { rs[b], gs[b], bs[b], a };
            line[1].color = { rs[b], gs[b], bs[b], a };
            w.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }
}

// ─── NEW: draw floating medical cross sparks ────────────────────────────────
struct CrossSpark {
    float x, y, vy, phase, size, spd;
};
static CrossSpark gSparks[30];
static bool gSparksInit = false;

void initSparks(float W, float H) {
    for (int i = 0; i < 30; i++) {
        gSparks[i] = {
            float(rand() % int(W)),
            float(rand() % int(H)),
            -(0.4f + (rand() % 8) / 10.f),
            float(rand() % 628) / 100.f,
            4.f + (rand() % 6),
            0.5f + (rand() % 5) / 10.f
        };
    }
}

void updateDrawSparks(sf::RenderWindow& w, float W, float H, float dt, float alpha) {
    for (int i = 0; i < 30; i++) {
        gSparks[i].y += gSparks[i].vy;
        gSparks[i].phase += dt * gSparks[i].spd;
        gSparks[i].x += std::sin(gSparks[i].phase * 0.7f) * 0.3f;
        if (gSparks[i].y < -20.f) {
            gSparks[i].y = H + 10.f;
            gSparks[i].x = float(rand() % int(W));
        }
        float pulse = 0.5f + 0.5f * std::sin(gSparks[i].phase * 2.f);
        uint8_t a = uint8_t(alpha * (0.15f + 0.35f * pulse));
        float s = gSparks[i].size;
        sf::RectangleShape h({ s * 2.5f, s * 0.7f });
        h.setOrigin({ s * 1.25f, s * 0.35f });
        h.setPosition({ gSparks[i].x, gSparks[i].y });
        h.setFillColor({ 0, 220, 240, a });
        w.draw(h);
        sf::RectangleShape v({ s * 0.7f, s * 2.5f });
        v.setOrigin({ s * 0.35f, s * 1.25f });
        v.setPosition({ gSparks[i].x, gSparks[i].y });
        v.setFillColor({ 0, 220, 240, a });
        w.draw(v);
    }
}

// ─── NEW: draw radial light rays from center ────────────────────────────────
void drawLightRays(sf::RenderWindow& w, float CX, float CY, float T, float alpha)
{
    const int RAYS = 12;
    for (int i = 0; i < RAYS; i++) {
        float baseAngle = float(i) / RAYS * 6.28f + T * 0.05f;
        float len = 400.f + 80.f * std::sin(T * 0.4f + i);
        float ex = CX + std::cos(baseAngle) * len;
        float ey = CY + std::sin(baseAngle) * len;
        float ww = 3.f + 5.f * std::sin(T * 0.3f + i * 0.7f);
        // draw as a thin wedge using two lines
        float perp = baseAngle + 1.5708f;
        sf::Vertex tri[3];
        tri[0].position = { CX, CY };
        tri[1].position = { ex + std::cos(perp) * ww, ey + std::sin(perp) * ww };
        tri[2].position = { ex - std::cos(perp) * ww, ey - std::sin(perp) * ww };
        uint8_t a = uint8_t(alpha * 0.025f);
        tri[0].color = { 0, 200, 230, a };
        tri[1].color = { 0, 200, 230, 0 };
        tri[2].color = { 0, 200, 230, 0 };
        w.draw(tri, 3, sf::PrimitiveType::Triangles);
    }
}

// ─── NEW: shimmer sweep effect for welcome title ─────────────────────────────
// draws a moving bright streak across the title area
void drawShimmer(sf::RenderWindow& w, float W, float H, float T, float alpha)
{
    float CX = W * 0.5f;
    float CY = H * 0.5f;
    // sweeping highlight band
    float sweep = std::fmod(T * 0.25f, 1.f); // 0..1 period ~4s
    float sx = CX - W * 0.38f + sweep * W * 0.76f;
    // diagonal shimmer band
    sf::ConvexShape band;
    band.setPointCount(4);
    float bw = W * 0.04f;
    float bh = H * 0.3f;
    band.setPoint(0, { sx - bw * 0.5f, CY - bh * 0.5f - H * 0.18f });
    band.setPoint(1, { sx + bw * 0.5f, CY - bh * 0.5f - H * 0.18f });
    band.setPoint(2, { sx + bw * 0.5f + bw, CY + bh * 0.5f - H * 0.18f });
    band.setPoint(3, { sx - bw * 0.5f + bw, CY + bh * 0.5f - H * 0.18f });
    band.setFillColor({ 200, 235, 255, uint8_t(alpha * 0.08f) });
    w.draw(band);
}

// ─── NEW: glowing halo behind the MediCore title ────────────────────────────
void drawTitleHalo(sf::RenderWindow& w, float CX, float titleY, float T, float alpha)
{
    float pulse = 0.5f + 0.5f * std::sin(T * 1.2f);
    for (int i = 8; i >= 1; i--) {
        float r = 160.f + i * 30.f;
        sf::CircleShape halo(r);
        halo.setOrigin({ r, r });
        halo.setPosition({ CX, titleY });
        halo.setFillColor({ 0, 160, 210, uint8_t(alpha * (0.012f + 0.008f * pulse) * (9 - i)) });
        w.draw(halo);
    }
}

// ─── NEW: decorative corner ornaments on welcome screen ─────────────────────
void drawCornerOrnaments(sf::RenderWindow& w, float W, float H, float alpha)
{
    float m = 32.f; // margin
    float len = 50.f;
    float thick = 1.5f;
    uint8_t a = uint8_t(alpha * 0.5f);
    sf::Color c{ 0, 210, 230, a };

    // helper: draw an L bracket at (ox,oy), flipped by (sx,sy)
    auto drawL = [&](float ox, float oy, float sx, float sy) {
        sf::RectangleShape h({ len, thick });
        h.setPosition({ ox, oy });
        h.setFillColor(c);
        if (sx < 0) h.setPosition({ ox - len, oy });
        w.draw(h);
        sf::RectangleShape v({ thick, len });
        v.setPosition({ ox, oy });
        v.setFillColor(c);
        if (sy < 0) v.setPosition({ ox, oy - len });
        w.draw(v);
        // small diamond at corner
        sf::RectangleShape dia({ 5.f, 5.f });
        dia.setOrigin({ 2.5f, 2.5f });
        dia.setRotation(sf::degrees(45));
        dia.setPosition({ ox, oy });
        dia.setFillColor(c);
        w.draw(dia);
        };

    drawL(m, m, 1, 1);
    drawL(W - m, m, -1, 1);
    drawL(m, H - m, 1, -1);
    drawL(W - m, H - m, -1, -1);
}

// ─── NEW: welcome screen side pillars (vertical accent lines) ────────────────
void drawSidePillars(sf::RenderWindow& w, float W, float H, float T, float alpha)
{
    float pulse = 0.5f + 0.5f * std::sin(T * 1.8f);
    uint8_t a = uint8_t(alpha * (0.15f + 0.08f * pulse));
    float px = W * 0.08f;
    float py = H * 0.15f;
    float ph = H * 0.70f;

    // left pillar
    sf::RectangleShape pl({ 1.f, ph });
    pl.setPosition({ px, py });
    pl.setFillColor({ 0, 200, 230, a });
    w.draw(pl);
    // tick marks
    for (int i = 0; i <= 6; i++) {
        float ty = py + ph * float(i) / 6.f;
        sf::RectangleShape tick({ 8.f, 1.f });
        tick.setPosition({ px - 4.f, ty });
        tick.setFillColor({ 0, 200, 230, uint8_t(a * 0.7f) });
        w.draw(tick);
    }
    // right pillar (mirror)
    sf::RectangleShape pr({ 1.f, ph });
    pr.setPosition({ W - px, py });
    pr.setFillColor({ 0, 200, 230, a });
    w.draw(pr);
    for (int i = 0; i <= 6; i++) {
        float ty = py + ph * float(i) / 6.f;
        sf::RectangleShape tick({ 8.f, 1.f });
        tick.setPosition({ W - px - 4.f, ty });
        tick.setFillColor({ 0, 200, 230, uint8_t(a * 0.7f) });
        w.draw(tick);
    }
}

void drawDoctor(sf::RenderWindow& w, float cx, float groundY,
    float scale, float phase, int dir, float alpha,
    bool hasCoat, sf::Color accent)
{
    float headR = 18.f * scale;
    float torsoH = 52.f * scale;
    float torsoW = 22.f * scale;
    float legH = 44.f * scale;
    float armH = 38.f * scale;
    float footW = 14.f * scale;
    float legSwing = std::sin(phase) * 18.f * scale;
    float armSwing = std::sin(phase + 3.14f) * 14.f * scale;
    float headBob = std::abs(std::sin(phase)) * 2.f * scale;
    uint8_t a = uint8_t(alpha);
    sf::Color skin{ 220, 180, 140, a };
    sf::Color coat{ 240, 245, 255, a };
    sf::Color dark{ 30,  40,  60, a };
    sf::Color steth{ accent.r, accent.g, accent.b, a };
    float headY = groundY - legH - torsoH - headR * 2.f - headBob;
    float torsoY = groundY - legH - torsoH;
    float hipY = groundY - legH;
    sf::RectangleShape leg1({ 6.f * scale, legH });
    leg1.setOrigin({ 3.f * scale, 0 });
    leg1.setPosition({ cx - 6.f * scale, hipY });
    leg1.setRotation(sf::degrees(legSwing * dir));
    leg1.setFillColor(dark);
    w.draw(leg1);
    sf::RectangleShape foot1({ footW, 5.f * scale });
    foot1.setPosition({ cx - 6.f * scale - footW * 0.5f + legSwing * dir * 0.3f, groundY - 5.f * scale });
    foot1.setFillColor(dark);
    w.draw(foot1);
    sf::RectangleShape leg2({ 6.f * scale, legH });
    leg2.setOrigin({ 3.f * scale, 0 });
    leg2.setPosition({ cx + 6.f * scale, hipY });
    leg2.setRotation(sf::degrees(-legSwing * dir));
    leg2.setFillColor({ 50,60,80,a });
    w.draw(leg2);
    sf::RectangleShape foot2({ footW, 5.f * scale });
    foot2.setPosition({ cx + 6.f * scale - footW * 0.5f - legSwing * dir * 0.3f, groundY - 5.f * scale });
    foot2.setFillColor({ 50,60,80,a });
    w.draw(foot2);
    sf::RectangleShape torso({ torsoW, torsoH });
    torso.setOrigin({ torsoW * 0.5f, 0 });
    torso.setPosition({ cx, torsoY });
    torso.setFillColor(hasCoat ? coat : sf::Color{ 80,120,180,a });
    w.draw(torso);
    if (hasCoat)
    {
        sf::RectangleShape lapel1({ 8.f * scale, torsoH * 0.6f });
        lapel1.setPosition({ cx - torsoW * 0.5f, torsoY });
        lapel1.setFillColor({ 200,210,230,a });
        w.draw(lapel1);
        sf::RectangleShape lapel2({ 8.f * scale, torsoH * 0.6f });
        lapel2.setPosition({ cx + torsoW * 0.5f - 8.f * scale, torsoY });
        lapel2.setFillColor({ 200,210,230,a });
        w.draw(lapel2);
    }
    sf::RectangleShape arm1({ 5.f * scale, armH });
    arm1.setOrigin({ 2.5f * scale, 0 });
    arm1.setPosition({ cx - torsoW * 0.5f, torsoY + 6.f * scale });
    arm1.setRotation(sf::degrees(armSwing * dir + 10.f));
    arm1.setFillColor(hasCoat ? coat : sf::Color{ 80,120,180,a });
    w.draw(arm1);
    sf::RectangleShape arm2({ 5.f * scale, armH });
    arm2.setOrigin({ 2.5f * scale, 0 });
    arm2.setPosition({ cx + torsoW * 0.5f, torsoY + 6.f * scale });
    arm2.setRotation(sf::degrees(-armSwing * dir - 10.f));
    arm2.setFillColor(hasCoat ? coat : sf::Color{ 80,120,180,a });
    w.draw(arm2);
    sf::CircleShape head(headR);
    head.setOrigin({ headR, headR });
    head.setPosition({ cx, headY + headR });
    head.setFillColor(skin);
    w.draw(head);
    sf::RectangleShape hair({ headR * 2.f, headR * 0.5f });
    hair.setOrigin({ headR, headR * 0.5f });
    hair.setPosition({ cx, headY + headR - headR * 0.8f });
    hair.setFillColor(dark);
    w.draw(hair);
    sf::CircleShape eye(2.f * scale);
    eye.setOrigin({ 2.f * scale, 2.f * scale });
    eye.setPosition({ cx + dir * 5.f * scale, headY + headR - 1.f * scale });
    eye.setFillColor(dark);
    w.draw(eye);
    sf::CircleShape stetHead(4.f * scale);
    stetHead.setOrigin({ 4.f * scale, 4.f * scale });
    stetHead.setPosition({ cx + dir * 6.f * scale, torsoY + torsoH * 0.5f });
    stetHead.setFillColor(steth);
    w.draw(stetHead);
    sf::RectangleShape tube({ 2.f * scale, torsoH * 0.35f });
    tube.setOrigin({ 1.f * scale, 0 });
    tube.setPosition({ cx + dir * 6.f * scale, torsoY + torsoH * 0.3f });
    tube.setFillColor(steth);
    w.draw(tube);
}

void drawHeartbeat(sf::RenderWindow& w, float y, float W, float offset, float alpha)
{
    static const int SEGS = 300;
    float spacing = W / SEGS;
    uint8_t a = uint8_t(alpha);
    for (int i = 0; i < SEGS - 1; i++)
    {
        float x1 = float(i) * spacing;
        float x2 = float(i + 1) * spacing;
        float t1 = (x1 / W + offset);
        float t2 = (x2 / W + offset);
        t1 -= int(t1);
        t2 -= int(t2);
        float spike1 = 0, spike2 = 0;
        if (t1 > 0.45f && t1 < 0.48f)       spike1 = -80.f * ((t1 - 0.45f) / 0.03f);
        else if (t1 >= 0.48f && t1 < 0.50f)  spike1 = -80.f + 160.f * ((t1 - 0.48f) / 0.02f);
        else if (t1 >= 0.50f && t1 < 0.52f)  spike1 = 80.f - 80.f * ((t1 - 0.50f) / 0.02f);
        if (t2 > 0.45f && t2 < 0.48f)        spike2 = -80.f * ((t2 - 0.45f) / 0.03f);
        else if (t2 >= 0.48f && t2 < 0.50f)  spike2 = -80.f + 160.f * ((t2 - 0.48f) / 0.02f);
        else if (t2 >= 0.50f && t2 < 0.52f)  spike2 = 80.f - 80.f * ((t2 - 0.50f) / 0.02f);
        sf::Vertex line[2];
        line[0].position = { x1, y + spike1 };
        line[1].position = { x2, y + spike2 };
        float brightness = 1.f - std::abs(spike1) / 160.f * 0.3f;
        line[0].color = { 0, uint8_t(200 * brightness), uint8_t(230 * brightness), a };
        line[1].color = { 0, uint8_t(200 * brightness), uint8_t(230 * brightness), a };
        w.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void drawBubble(sf::RenderWindow& w, float cx, float cy, float scale, float alpha)
{
    uint8_t a = uint8_t(alpha * 0.7f);
    sf::CircleShape b(14.f * scale);
    b.setOrigin({ 14.f * scale,14.f * scale });
    b.setPosition({ cx,cy });
    b.setFillColor({ 255,255,255,a });
    w.draw(b);
    for (int i = 0; i < 3; i++) {
        sf::CircleShape dot(2.f * scale);
        dot.setOrigin({ 2.f * scale,2.f * scale });
        dot.setPosition({ cx - 6.f * scale + i * 6.f * scale, cy });
        dot.setFillColor({ 0,150,180,a });
        w.draw(dot);
    }
    sf::ConvexShape tail;
    tail.setPointCount(3);
    tail.setPoint(0, { cx - 4.f * scale, cy + 10.f * scale });
    tail.setPoint(1, { cx + 4.f * scale, cy + 10.f * scale });
    tail.setPoint(2, { cx, cy + 20.f * scale });
    tail.setFillColor({ 255,255,255,a });
    w.draw(tail);
}

int main()
{
    srand((unsigned)time(nullptr));

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "MediCore", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    float W = float(desktop.size.x);
    float H = float(desktop.size.y);
    float CX = W * 0.5f, CY = H * 0.5f;

    sf::Font fontTitle, fontSub;
    fontTitle.openFromFile("Cinzel-Bold.ttf");
    fontSub.openFromFile("Raleway-Light.ttf");

    initSparks(W, H);

    static const int NP = 100;
    struct Particle { sf::Vector2f pos, vel; float r, phase, spd; int type; };
    Particle parts[NP];
    for (int i = 0; i < NP; i++) {
        parts[i] = { {float(rand() % int(W)),float(rand() % int(H))},
                  {(rand() % 200 - 100) / 300.f,(rand() % 200 - 100) / 300.f},
                  1.f + (rand() % 10) / 4.f, float(rand() % 628) / 100.f,
                  0.3f + (rand() % 7) / 10.f, rand() % 3 };
    }

    struct Ring { float r, phase, spd; };
    Ring rings[5] =
    {
        {H * .28f,0.f,.20f},{H * .42f,1.f,.13f},{H * .58f,2.f,.08f},
        {H * .74f,3.f,.05f},{H * .90f,4.f,.03f}
    };

    struct Doctor
    {
        float x, y, speed, phase, scale;
        int   dir;
        bool  coat;
        sf::Color accent;
        float alpha;
        bool  bubbleVisible;
        float bubbleTimer;
    };

    Doctor docs[3];
    docs[0] = { -120.f, H * 0.72f, 90.f, 0.f,  1.1f,  1, true,  {0,210,230}, 255.f, false, 0.f };
    docs[1] = { W + 100.f, H * 0.68f, 85.f, 1.5f, 1.0f, -1, true,  {0,230,170}, 255.f, false, 1.5f };
    docs[2] = { -200.f, H * 0.78f, 55.f, 3.0f, 0.75f,  1, false, {180,200,230}, 180.f, false, 2.8f };

    // ─── DNA helix positions (3 helixes flanking center) ─────────────────────
    float helixPositions[3] = { W * 0.15f, W * 0.5f, W * 0.85f };

    struct Word
    {
        const char* text;
        float       x, y;
        unsigned    size;
        sf::Color   col;
        bool        useTitle;
        float       delay;
        float       alpha;
        float       slideY;
    };

    unsigned BIG = unsigned(H * 0.13f);
    unsigned MED = unsigned(H * 0.052f);
    unsigned SML = unsigned(H * 0.034f);
    unsigned TINY = unsigned(H * 0.022f);

    Word words[] =
    {
        {"Welcome",              0,CY - H * .30f, MED, {160,200,230,255}, false, 0.f, 0.f, 60.f},
        {"to",                   0,CY - H * .30f, MED, {160,200,230,255}, false, 0.f, 0.f, 60.f},
        {"MediCore",             0,CY - H * .12f, BIG, {255,255,255,255}, true,  0.f, 0.f, 60.f},
        {"Hospital",             0,CY + H * .07f, SML, {0,210,230,255},   false, 0.f, 0.f, 60.f},
        {"Management",           0,CY + H * .07f, SML, {0,210,230,255},   false, 0.f, 0.f, 60.f},
        {"System",               0,CY + H * .07f, SML, {0,210,230,255},   false, 0.f, 0.f, 60.f},
        {"Your Health. Our Priority.", 0,CY + H * .20f,TINY,{100,150,190,255},false,0.f,0.f,60.f},
    };
    static const int NW = 7;

    {
        float gap = W * 0.016f;
        float w0, w1, w2, w3, w4, w5, w6;
        { sf::Text t(fontSub, "Welcome", MED);   w0 = t.getLocalBounds().size.x; }
        { sf::Text t(fontSub, "to", MED);        w1 = t.getLocalBounds().size.x; }
        { sf::Text t(fontTitle, "MediCore", BIG); w2 = t.getLocalBounds().size.x; }
        { sf::Text t(fontSub, "Hospital", SML);  w3 = t.getLocalBounds().size.x; }
        { sf::Text t(fontSub, "Management", SML); w4 = t.getLocalBounds().size.x; }
        { sf::Text t(fontSub, "System", SML);    w5 = t.getLocalBounds().size.x; }
        { sf::Text t(fontSub, "Your Health. Our Priority.", TINY); w6 = t.getLocalBounds().size.x; }
        float line0W = w0 + gap + w1;
        words[0].x = CX - line0W * 0.5f + w0 * 0.5f;
        words[1].x = CX - line0W * 0.5f + w0 + gap + w1 * 0.5f;
        words[2].x = CX;
        float line2W = w3 + gap + w4 + gap + w5;
        words[3].x = CX - line2W * 0.5f + w3 * 0.5f;
        words[4].x = CX - line2W * 0.5f + w3 + gap + w4 * 0.5f;
        words[5].x = CX - line2W * 0.5f + w3 + gap + w4 + gap + w5 * 0.5f;
        words[6].x = CX;
        float base = 7.2f;
        float delays[NW] = { 0.f,0.5f,1.2f,2.2f,2.8f,3.4f,4.6f };
        for (int i = 0; i < NW; i++) words[i].delay = base + delays[i];
    }

    const float PHASE_WALK = 5.5f;
    const float PHASE_FLASH = 7.0f;
    const float PHASE_MISSION_START = 12.0f;

    float flashAlpha = 0.f;
    float bgAlpha = 0.f;
    float heartOffset = 0.f;
    float missionAlpha = 0.f;
    float crawlY = H;

    sf::Clock clock;
    float T = 0;

    while (window.isOpen())
    {
        while (auto ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>()) window.close();
            if (const auto* k = ev->getIf<sf::Event::KeyPressed>())
                if (k->code == sf::Keyboard::Key::Escape) window.close();
        }

        float dt = clock.restart().asSeconds();
        T += dt;

        for (int i = 0; i < 3; i++)
        {
            docs[i].phase += dt * 3.5f;
            docs[i].x += docs[i].speed * docs[i].dir * dt;
            docs[i].bubbleTimer += dt;
            if (docs[i].bubbleTimer > 2.5f)
            {
                docs[i].bubbleVisible = !docs[i].bubbleVisible;
                docs[i].bubbleTimer = 0.f;
            }
            if (T > PHASE_WALK)
            {
                float t = clamp01((T - PHASE_WALK) / 1.0f);
                docs[i].alpha = 255.f * (1.f - t);
            }
        }

        if (T > PHASE_WALK && T < PHASE_FLASH)
        {
            float t = clamp01((T - PHASE_WALK) / (PHASE_FLASH - PHASE_WALK));
            float peak = t < 0.5f ? t * 2.f : (1.f - t) * 2.f;
            flashAlpha = peak * 255.f;
        }

        if (T > PHASE_FLASH)
        {
            bgAlpha += 255.f * dt * 0.8f;
            if (bgAlpha > 255.f) bgAlpha = 255.f;
        }

        for (int i = 0; i < NW; i++)
        {
            if (T > words[i].delay)
            {
                words[i].alpha += 255.f * dt * 1.6f;
                if (words[i].alpha > 255.f) words[i].alpha = 255.f;
                words[i].slideY -= 60.f * dt * 2.8f;
                if (words[i].slideY < 0.f) words[i].slideY = 0.f;
            }
        }

        if (T > PHASE_MISSION_START)
        {
            missionAlpha += 255.f * dt * 0.6f;
            if (missionAlpha > 255.f) missionAlpha = 255.f;
            if (crawlY > H * 0.20f)
                crawlY -= H * 0.10f * dt;
        }

        for (int i = 0; i < NP; i++)
        {
            parts[i].pos += parts[i].vel;
            parts[i].phase += dt * parts[i].spd;
            if (parts[i].pos.x<0 || parts[i].pos.x>W) parts[i].vel.x *= -1;
            if (parts[i].pos.y<0 || parts[i].pos.y>H) parts[i].vel.y *= -1;
        }
        for (int i = 0; i < 5; i++) rings[i].phase += dt * rings[i].spd;
        heartOffset += dt * 0.18f;
        if (heartOffset > 1.f) heartOffset -= 1.f;

        float bob = std::sin(T * 0.95f) * 5.f;

        window.clear({ 3,10,24 });

        // ── background gradient strips (unchanged) ──────────────────────────
        for (int i = 0; i < 20; i++)
        {
            sf::RectangleShape s({ W,H / 20.f });
            s.setPosition({ 0.f,float(i) * H / 20.f });
            float tt = float(i) / 20.f;
            s.setFillColor({ uint8_t(3 + tt * 5),uint8_t(10 + tt * 9),uint8_t(24 + tt * 22) });
            window.draw(s);
        }

        // ── grid lines (unchanged) ──────────────────────────────────────────
        for (int i = 0; i < 28; i++)
        {
            sf::RectangleShape h({ W,1.f });
            h.setPosition({ 0.f,float(i) * H / 28.f });
            h.setFillColor({ 0,55,95,7 });
            window.draw(h);
            sf::RectangleShape v({ 1.f,H });
            v.setPosition({ float(i) * W / 28.f,0.f });
            v.setFillColor({ 0,55,95,7 });
            window.draw(v);
        }

        // ── NEW: aurora waves behind everything in pre-flash ────────────────
        if (T < PHASE_FLASH + 0.5f) {
            float auroraA = std::min(T / 2.f, 1.f) * 255.f;
            if (T > PHASE_WALK) auroraA *= 1.f - clamp01((T - PHASE_WALK) / 1.5f);
            drawAuroraWaves(window, W, H, T, auroraA);
        }

        // ── glow circles (unchanged) ────────────────────────────────────────
        float gr = H * (0.18f + 0.025f * std::sin(T * 1.4f));
        for (int i = 8; i >= 1; i--) {
            float ri = gr * (1.f + i * .44f);
            sf::CircleShape gc(ri);
            gc.setOrigin({ ri,ri });
            gc.setPosition({ CX,CY });
            gc.setFillColor({ 0,160,210,uint8_t(i < 2 ? 1 : i - 1) });
            window.draw(gc);
        }

        // ── rings (unchanged) ───────────────────────────────────────────────
        for (int i = 0; i < 5; i++) {
            float wave = 0.5f + 0.5f * std::sin(rings[i].phase);
            sf::CircleShape ring(rings[i].r);
            ring.setOrigin({ rings[i].r,rings[i].r });
            ring.setPosition({ CX,CY });
            ring.setFillColor(sf::Color::Transparent);
            ring.setOutlineThickness(1.2f);
            ring.setOutlineColor({ 0,200,230,uint8_t(6 + 22 * wave) });
            window.draw(ring);
        }

        // ── particles (unchanged) ───────────────────────────────────────────
        for (int i = 0; i < NP; i++) {
            float a = 22.f + 42.f * std::abs(std::sin(parts[i].phase));
            if (parts[i].type == 0) {
                sf::CircleShape c(parts[i].r);
                c.setFillColor({ 0,200,230,uint8_t(a) });
                c.setPosition(parts[i].pos - sf::Vector2f{ parts[i].r,parts[i].r });
                window.draw(c);
            }
            else if (parts[i].type == 1)
            {
                float rr = parts[i].r + 1.f;
                sf::CircleShape c(rr);
                c.setFillColor(sf::Color::Transparent);
                c.setOutlineThickness(1.f);
                c.setOutlineColor({ 0,230,160,uint8_t(a * .6f) });
                c.setPosition(parts[i].pos - sf::Vector2f{ rr,rr });
                window.draw(c);
            }
            else
            {
                float rr = parts[i].r;
                sf::RectangleShape h({ rr * 3.f,1.f });
                h.setFillColor({ 0,200,230,uint8_t(a) });
                h.setPosition(parts[i].pos - sf::Vector2f{ rr * 1.5f,0.f });
                window.draw(h);
                sf::RectangleShape v({ 1.f,rr * 3.f });
                v.setFillColor({ 0,200,230,uint8_t(a) });
                v.setPosition(parts[i].pos - sf::Vector2f{ 0.f,rr * 1.5f });
                window.draw(v);
            }
        }

        // ═══════════════════════════════════════════════════════════════════
        // PRE-FLASH SCENE  (all original logic preserved, new beauty added)
        // ═══════════════════════════════════════════════════════════════════
        if (T < PHASE_FLASH + 0.3f)
        {
            // ── NEW: light rays emanating from center ───────────────────────
            float rayA = std::min(T / 3.f, 1.f) * 255.f;
            if (T > PHASE_WALK) rayA *= 1.f - clamp01((T - PHASE_WALK) / 1.2f);
            drawLightRays(window, CX, CY, T, rayA);

            // ── NEW: DNA helixes on left, center, right ─────────────────────
            float helixA = std::min(T / 2.5f, 1.f) * 255.f;
            if (T > PHASE_WALK) helixA *= 1.f - clamp01((T - PHASE_WALK) / 1.2f);
            for (int h = 0; h < 3; h++) {
                float hx = helixPositions[h];
                float hy = H * (h == 1 ? 0.40f : 0.45f);
                drawDNAHelix(window, hx, hy, T + h * 1.2f, helixA);
            }

            // ── NEW: floating medical cross sparks ──────────────────────────
            float sparkA = std::min(T / 2.f, 1.f) * 255.f;
            if (T > PHASE_WALK) sparkA *= 1.f - clamp01((T - PHASE_WALK) / 1.f);
            updateDrawSparks(window, W, H, dt, sparkA);

            // ── floor line + glow (unchanged) ──────────────────────────────
            sf::RectangleShape floor({ W, 2.f });
            floor.setPosition({ 0.f, H * 0.80f });
            floor.setFillColor({ 0,180,210,60 });
            window.draw(floor);
            sf::RectangleShape floorGlow({ W, 30.f });
            floorGlow.setPosition({ 0.f, H * 0.80f });
            floorGlow.setFillColor({ 0,150,190,15 });
            window.draw(floorGlow);

            // ── NEW: floor reflection shimmer ───────────────────────────────
            {
                float shimPhase = std::fmod(T * 0.4f, 1.f);
                float sx = shimPhase * W;
                sf::RectangleShape shim({ W * 0.12f, 8.f });
                shim.setPosition({ sx - W * 0.06f, H * 0.800f });
                shim.setFillColor({ 0, 200, 240, 12 });
                window.draw(shim);
            }

            drawHeartbeat(window, H * 0.87f, W, heartOffset,
                T < PHASE_WALK ? 120.f : 120.f * (1.f - clamp01((T - PHASE_WALK) / 1.f)));

            // ── logo top-left (unchanged) ───────────────────────────────────
            {
                float logoA = clamp01(T / 1.5f) * 200.f;
                sf::Text logo(fontTitle, "MediCore", unsigned(H * 0.055f));
                logo.setFillColor({ 255,255,255,uint8_t(logoA) });
                logo.setPosition({ W * 0.04f, H * 0.04f });
                window.draw(logo);
                sf::Text sub(fontSub, "Hospital Management System", unsigned(H * 0.022f));
                sub.setFillColor({ 0,210,230,uint8_t(logoA * 0.8f) });
                sub.setPosition({ W * 0.04f, H * 0.04f + H * 0.065f });
                window.draw(sub);
                sf::Text cross(fontTitle, "+", unsigned(H * 0.055f));
                cross.setFillColor({ 0,210,230,uint8_t(logoA) });
                auto b = cross.getLocalBounds();
                cross.setPosition({ W * 0.04f - b.size.x - W * 0.015f, H * 0.03f });
                window.draw(cross);
            }

            // ── doctors (unchanged) ─────────────────────────────────────────
            for (int i = 2; i >= 0; i--)
            {
                drawDoctor(window, docs[i].x, H * 0.80f, docs[i].scale, docs[i].phase,
                    docs[i].dir, docs[i].alpha, docs[i].coat, docs[i].accent);
                if (docs[i].bubbleVisible && docs[i].alpha > 80.f)
                {
                    float headTop = H * 0.80f - (44.f + 52.f + 36.f + 18.f) * docs[i].scale;
                    drawBubble(window, docs[i].x + docs[i].dir * 20.f * docs[i].scale,
                        headTop - 30.f * docs[i].scale, docs[i].scale, docs[i].alpha);
                }
            }

            // ── hint text (unchanged) ───────────────────────────────────────
            if (T < PHASE_WALK)
            {
                float pulse = 0.5f + 0.5f * std::sin(T * 2.f);
                sf::Text hint(fontSub, "Welcome to MediCore", unsigned(H * 0.020f));
                hint.setFillColor({ 100,150,190,uint8_t(80 + 60 * pulse) });
                auto b = hint.getLocalBounds();
                hint.setOrigin({ b.position.x + b.size.x * .5f, b.position.y + b.size.y * .5f });
                hint.setPosition({ CX, H * 0.93f });
                window.draw(hint);
            }
        }

        // ═══════════════════════════════════════════════════════════════════
        // WELCOME SCREEN  (all original logic preserved, new beauty added)
        // ═══════════════════════════════════════════════════════════════════
        if (T > PHASE_FLASH - 0.5f)
        {
            sf::RectangleShape dim({ W,H });
            dim.setFillColor({ 3,10,24,uint8_t(bgAlpha * 0.5f) });
            window.draw(dim);

            if (bgAlpha > 30.f)
            {
                // ── NEW: corner ornaments ───────────────────────────────────
                drawCornerOrnaments(window, W, H, bgAlpha);

                // ── NEW: side pillar accents ────────────────────────────────
                drawSidePillars(window, W, H, T, bgAlpha);

                // ── NEW: title halo glow ────────────────────────────────────
                float titleY = words[2].y + words[2].slideY + bob;
                if (words[2].alpha > 0.f)
                    drawTitleHalo(window, CX, titleY, T, words[2].alpha / 255.f * bgAlpha / 255.f);

                // ── NEW: shimmer sweep on title ─────────────────────────────
                if (words[2].alpha > 120.f)
                    drawShimmer(window, W, H, T, words[2].alpha);

                // ── cross (unchanged) ───────────────────────────────────────
                float pulse = 0.5f + 0.5f * std::sin(T * 2.4f);
                sf::Text cross(fontTitle, "+", unsigned(H * .10f));
                auto b = cross.getLocalBounds();
                cross.setOrigin({ b.position.x + b.size.x * .5f, b.position.y + b.size.y * .5f });
                cross.setPosition({ CX, CY - H * .32f + bob });
                cross.setFillColor({ 0,uint8_t(160 + 95 * pulse),230, uint8_t(bgAlpha) });
                window.draw(cross);
            }

            // ── decorative rules (unchanged) ────────────────────────────────
            if (words[2].alpha > 80.f)
            {
                float ruleY = CY + H * .005f + bob;
                float ra = words[2].alpha;
                sf::RectangleShape rl({ W * .18f,1.5f });
                rl.setPosition({ CX - W * .21f,ruleY });
                rl.setFillColor({ 0,210,230,uint8_t(ra * .8f) });
                window.draw(rl);
                sf::RectangleShape rr({ W * .18f,1.5f });
                rr.setPosition({ CX + W * .03f,ruleY });
                rr.setFillColor({ 0,210,230,uint8_t(ra * .8f) });
                window.draw(rr);
                sf::RectangleShape dia({ 8.f,8.f });
                dia.setOrigin({ 4.f,4.f });
                dia.setRotation(sf::degrees(45));
                dia.setPosition({ CX,ruleY });
                dia.setFillColor({ 0,210,230,uint8_t(ra) });
                window.draw(dia);

                // ── NEW: secondary thin rule above main rule ─────────────────
                sf::RectangleShape rl2({ W * .12f, 0.5f });
                rl2.setPosition({ CX - W * .17f, ruleY - 6.f });
                rl2.setFillColor({ 0, 180, 210, uint8_t(ra * 0.3f) });
                window.draw(rl2);
                sf::RectangleShape rr2({ W * .12f, 0.5f });
                rr2.setPosition({ CX + W * .05f, ruleY - 6.f });
                rr2.setFillColor({ 0, 180, 210, uint8_t(ra * 0.3f) });
                window.draw(rr2);
            }

            // ── words (unchanged render, unchanged data) ────────────────────
            for (int i = 0; i < NW; i++)
            {
                if (words[i].alpha <= 0.f) continue;
                sf::Color col = words[i].col;
                col.a = uint8_t(words[i].alpha);
                float fy = words[i].y + words[i].slideY + bob;
                if (i == 2)
                {
                    for (int g = 5; g >= 1; g--)
                    {
                        sf::Text sh(fontTitle, words[i].text, words[i].size);
                        auto b = sh.getLocalBounds();
                        sh.setOrigin({ b.position.x + b.size.x * .5f, b.position.y + b.size.y * .5f });
                        sh.setPosition({ words[i].x + float(g) * .5f,fy + float(g) * .5f });
                        sh.setFillColor({ 0,180,220,uint8_t(words[i].alpha / 5 / g) });
                        window.draw(sh);
                    }
                }
                sf::Font& f = (words[i].useTitle) ? fontTitle : fontSub;
                sf::Text t(f, words[i].text, words[i].size);
                auto b = t.getLocalBounds();
                t.setOrigin({ b.position.x + b.size.x * .5f, b.position.y + b.size.y * .5f });
                t.setPosition({ words[i].x,fy });
                t.setFillColor(col);
                window.draw(t);
            }

            // ── ESC hint (unchanged) ────────────────────────────────────────
            {
                float ha = clamp01((T - PHASE_FLASH - 1.f) / 2.f) * 80.f;
                sf::Text esc(fontSub, "ESC — Exit", unsigned(H * .016f));
                esc.setFillColor({ 50,80,120,uint8_t(ha) });
                esc.setPosition({ 16.f,H - H * .036f });
                window.draw(esc);
            }
        }

        // ═══════════════════════════════════════════════════════════════════
        // MISSION CRAWL  (completely unchanged)
        // ═══════════════════════════════════════════════════════════════════
        if (missionAlpha > 0.f)
        {
            sf::RectangleShape overlay({ W, H });
            overlay.setFillColor({ 3, 8, 20, uint8_t(missionAlpha * 0.93f) });
            window.draw(overlay);

            const char* lines[] =
            {
                "Our Team  |  MediCore",
                "",
                "The People Powering Healthcare Innovation",
                "",
                "At MediCore, our greatest strength lies in our people,",
                "a passionate team of innovators, healthcare professionals,",
                "and technologists united by a shared mission:",
                "to make healthcare smarter, faster, and more accessible",
                "for everyone.",
                "",
                "From developing cutting-edge hospital management systems",
                "to empowering patients and providers with digital tools,",
                "every member of our team plays a vital role in",
                "transforming the future of healthcare",
                "in Pakistan and beyond.",
            };
            static const int NL = 15;

            float lineSpacing = H * 0.052f;
            for (int i = 0; i < NL; i++)
            {
                float y = crawlY + i * lineSpacing;
                if (y > H + 10.f || y < -60.f) continue;
                if (lines[i][0] == '\0') continue;
                float tPers = 1.f - clamp01(y / H);
                float scale = clamp01(1.f - tPers * 0.52f);
                float fadeTop = clamp01(y / (H * 0.38f));
                uint8_t a = uint8_t(fadeTop * missionAlpha);
                bool isHeader = (i == 0);
                bool isTitle = (i == 2);
                sf::Font& f = (isHeader || isTitle) ? fontTitle : fontSub;
                unsigned sz = isHeader ? unsigned(H * 0.036f * scale)
                    : isTitle ? unsigned(H * 0.046f * scale)
                    : unsigned(H * 0.028f * scale);
                sf::Color col = isHeader ? sf::Color{ 0,210,230,a }
                    : isTitle ? sf::Color{ 255,255,255,a }
                : sf::Color{ 160,200,230,a };
                sf::Text txt(f, lines[i], sz);
                auto b = txt.getLocalBounds();
                txt.setOrigin({ b.position.x + b.size.x * 0.5f, b.position.y + b.size.y * 0.5f });
                txt.setPosition({ CX, y });
                txt.setFillColor(col);
                window.draw(txt);
            }

            sf::RectangleShape vigL({ W * 0.10f, H });
            vigL.setPosition({ 0.f, 0.f });
            vigL.setFillColor({ 3,8,20,190 });
            window.draw(vigL);

            sf::RectangleShape vigR({ W * 0.10f, H });
            vigR.setPosition({ W - W * 0.10f, 0.f });
            vigR.setFillColor({ 3,8,20,190 });
            window.draw(vigR);

            sf::RectangleShape topFade({ W, H * 0.38f });
            topFade.setPosition({ 0.f, 0.f });
            topFade.setFillColor({ 3,8,20,210 });
            window.draw(topFade);

            float ha = clamp01((T - PHASE_MISSION_START) / 1.5f);
            sf::Text header(fontTitle, "Our Team  |  MediCore", unsigned(H * 0.030f));
            auto bh = header.getLocalBounds();
            header.setOrigin({ bh.position.x + bh.size.x * 0.5f, bh.position.y + bh.size.y * 0.5f });
            header.setPosition({ CX, H * 0.07f });
            header.setFillColor({ 0,210,230,uint8_t(ha * 180) });
            window.draw(header);

            sf::RectangleShape rule({ W * 0.28f, 1.f });
            rule.setOrigin({ W * 0.14f, 0.5f });
            rule.setPosition({ CX, H * 0.115f });
            rule.setFillColor({ 0,210,230,uint8_t(ha * 120) });
            window.draw(rule);
        }

        // ── flash (unchanged) ───────────────────────────────────────────────
        if (flashAlpha > 1.f)
        {
            sf::RectangleShape flash({ W,H });
            flash.setFillColor({ 220,240,255,uint8_t(flashAlpha) });
            window.draw(flash);
        }

        window.display();
    }
}