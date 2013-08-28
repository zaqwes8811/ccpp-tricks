% function [ output_args ] = test( input_args )
%TEST Summary of this function goes here
%  Detailed explanation goes here
fid=fopen('Out_st_one.txt','r'); 
    data=str2num(fgetl(fid)); % коэффициенты в прямом коде со знаком и целые

fclose(fid);
%
request=256;
i=0:1:request-1;

tru=(2^(8-1)-1)*(1*sin(2*pi*i/request)+1*cos(2*pi*i/request))/2^0.5;
%

stem(data)
hold on
grid on
plot(tru,'rV')
% спектр
figure
stem(20*log10(abs(fft(data/2^7))))
grid on