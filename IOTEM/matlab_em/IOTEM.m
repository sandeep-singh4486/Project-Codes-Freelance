function varargout = IOTEM(varargin)
% IOTEM MATLAB code for IOTEM.fig
%      IOTEM, by itself, creates a new IOTEM or raises the existing
%      singleton*.
%
%      H = IOTEM returns the handle to a new IOTEM or the handle to
%      the existing singleton*.
%
%      IOTEM('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in IOTEM.M with the given input arguments.
%
%      IOTEM('Property','Value',...) creates a new IOTEM or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before IOTEM_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to IOTEM_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help IOTEM

% Last Modified by GUIDE v2.5 28-May-2017 17:33:12

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @IOTEM_OpeningFcn, ...
                   'gui_OutputFcn',  @IOTEM_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before IOTEM is made visible.
function IOTEM_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to IOTEM (see VARARGIN)

% Choose default command line output for IOTEM
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes IOTEM wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = IOTEM_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function current_Callback(hObject, eventdata, handles)
% hObject    handle to current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of current as text
%        str2double(get(hObject,'String')) returns contents of current as a double


% --- Executes during object creation, after setting all properties.
function current_CreateFcn(hObject, eventdata, handles)
% hObject    handle to current (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
% --- Executes on button press in start.
function start_Callback(hObject, eventdata, handles)
% hObject    handle to start (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
x= 0;
time=60;
voltage=230;
amps = 0;
  totamps =  0;
  avgamps =  0; 
  amphr =  0;
  watt =  0; 
  energy = (watt * time) / 3600; 
global a;
for i = 1:100
    v = readVoltage(a, 'A0');
   amps = abs(v-519)/100 ; 
  totamps = totamps + amps; 
  avgamps = totamps / time; 
  amphr = (avgamps * time) ;
  watt = voltage * amps; 
  energy = (watt * time) / 3600; 
    disp(amps);
    x= [x amps];
    plot(handles.axes1,x)
    grid;
    set(handles.current,'String',num2str(amps));
     set(handles.POWER,'String',num2str(watt))
      set(handles.ENERGY,'String',num2str(energy))
    pause(1);
    thingSpeakURL = 'http://api.thingspeak.com/';
thingSpeakWriteURL = [thingSpeakURL 'update'];
writeApiKey = 'GG4DLN8BA3Y0N4VL';
fieldName = 'field1';
fieldValue = amps;
fieldName = 'field2';
fieldValue = watt;
fieldName = 'field3';
fieldValue = energy;
response = webwrite(thingSpeakWriteURL,'api_key',writeApiKey,fieldName,fieldValue)

end   
guidata(hobject,handles);


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
clear a;



function POWER_Callback(hObject, eventdata, handles)
% hObject    handle to POWER (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of POWER as text
%        str2double(get(hObject,'String')) returns contents of POWER as a double


% --- Executes during object creation, after setting all properties.
function POWER_CreateFcn(hObject, eventdata, handles)
% hObject    handle to POWER (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ENERGY_Callback(hObject, eventdata, handles)
% hObject    handle to ENERGY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ENERGY as text
%        str2double(get(hObject,'String')) returns contents of ENERGY as a double


% --- Executes during object creation, after setting all properties.
function ENERGY_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ENERGY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Amount_Callback(hObject, eventdata, handles)
% hObject    handle to Amount (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Amount as text
%        str2double(get(hObject,'String')) returns contents of Amount as a double


% --- Executes during object creation, after setting all properties.
function Amount_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Amount (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
