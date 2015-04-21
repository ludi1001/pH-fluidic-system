ph = phdata(:,1);
back = phdata(:,2);
red = phdata(:,3);
green = phdata(:,4);
blue = phdata(:,5);


ph_linspace = linspace(6.6, 7.9);
% green
[p_green, p_green_r] = polyfit(ph, green, 1);
figure(1)
plot(ph, green, 'go', ph_linspace, polyval(p_green, ph_linspace), 'k-')
xlabel('pH'), ylabel('Transmittance (a.u.)')
SSresid_green = sum((green - polyval(p_green, ph)).^2);
SStotal_green = (length(green) - 1) * var(green);
rsq_green = 1 - SSresid_green/SStotal_green

% blue
figure(2)
plot(ph, blue, 'bo')

% green with blue calibration
[p_green_2, p_green_2_r] = polyfit(ph, green - blue, 1);
figure(2)
plot(ph, green - blue, 'go', ph_linspace, polyval(p_green_2, ph_linspace), 'k-')
SSresid_green_2 = sum((green - blue - polyval(p_green_2, ph)).^2);
SStotal_green_2 = (length(green) - 1) * var(green - blue);
rsq_green_2 = 1 - SSresid_green_2/SStotal_green_2