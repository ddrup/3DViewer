#version 330 core

uniform float u_dashSize;
uniform float u_gapSize;
uniform int u_shape;
uniform int u_typeVertex; // 0 - квадратные, 1 - круглые
uniform float u_pointSize;

in vec3 fregColor;

void main()
{
    if (u_shape == 1) {
        // Вычисляем расстояние до ближайшей линии
        float distance = length(gl_FragCoord.xy);

        // Вычисляем шаблон пунктира
        float pattern = u_dashSize + u_gapSize;
        float visibility = fract(distance / pattern);

        // Проверяем, находится ли фрагмент в пробеле
        if (visibility > u_dashSize / pattern) {
            discard; // Отбрасываем фрагмент, если он находится в пробеле
        }
        gl_FragColor = vec4(fregColor, 1.0);
    } else if (u_shape == 0) {
        // Если вершина должна быть круглая
        if (u_typeVertex == 1) {
            vec2 pointCoord = gl_PointCoord * 2.0 - 1.0;
            float dist = dot(pointCoord, pointCoord);
            if (dist > 2.0) {
                discard; // Отбрасываем фрагмент, если он за пределами круга
            } else {
                gl_FragColor = vec4(fregColor, 1.0);
            }
        } else {
            gl_FragColor = vec4(fregColor, 1.0);
        }

    }
}
