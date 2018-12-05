object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'CryptopiaScan'
  ClientHeight = 560
  ClientWidth = 800
  Color = cl3DLight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  OnActivate = FormActivate
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 380
    Top = 8
    Width = 210
    Height = 97
    Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100'!'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 205
    Top = 8
    Width = 161
    Height = 97
    Caption = #1050#1072#1082#1080#1077' '#1087#1072#1088#1099' '#1089#1082#1072#1085#1080#1088#1086#1074#1072#1090#1100'?'
    Color = clSilver
    ParentBackground = False
    ParentColor = False
    TabOrder = 1
    object Label5: TLabel
      Left = 16
      Top = 71
      Width = 74
      Height = 13
      Caption = 'BaseVolume '#1079#1072' '
    end
    object Label7: TLabel
      Left = 120
      Top = 71
      Width = 29
      Height = 13
      Caption = #1095#1072#1089#1086#1074
    end
    object RadioButton1: TRadioButton
      Left = 16
      Top = 22
      Width = 129
      Height = 17
      Caption = #1058#1086#1083#1100#1082#1086' '#1089' BTC'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 16
      Top = 45
      Width = 113
      Height = 17
      Caption = #1058#1086#1083#1100#1082#1086' '#1089' USDT'
      TabOrder = 1
      OnClick = RadioButton2Click
    end
    object Edit4: TEdit
      Left = 91
      Top = 68
      Width = 23
      Height = 21
      NumbersOnly = True
      TabOrder = 2
      Text = '24'
    end
  end
  object Button2: TButton
    Left = 604
    Top = 8
    Width = 186
    Height = 97
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Memo2: TMemo
    Left = 1104
    Top = 448
    Width = 95
    Height = 90
    Lines.Strings = (
      'Memo2')
    TabOrder = 3
    Visible = False
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 111
    Width = 257
    Height = 441
    BiDiMode = bdLeftToRight
    Color = clSilver
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentBiDiMode = False
    ParentColor = False
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 4
    object Label4: TLabel
      Left = 48
      Top = 21
      Width = 76
      Height = 19
      Caption = #1048#1085#1090#1077#1088#1074#1072#1083':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 175
      Top = 21
      Width = 33
      Height = 19
      Caption = #1084#1080#1085'.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Edit5: TEdit
      Left = 130
      Top = 18
      Width = 39
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '0.1'
    end
    object Memo1: TMemo
      Left = 12
      Top = 237
      Width = 229
      Height = 188
      Lines.Strings = (
        'Memo1')
      TabOrder = 1
    end
    object GroupBox2: TGroupBox
      Left = 12
      Top = 51
      Width = 229
      Height = 110
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1086#1073#1098#1105#1084#1086#1074
      TabOrder = 2
      object Label1: TLabel
        Left = 23
        Top = 27
        Width = 120
        Height = 13
        Caption = #1056#1072#1079#1085#1080#1094#1072' BaseVolume >='
      end
      object Label2: TLabel
        Left = 6
        Top = 54
        Width = 137
        Height = 13
        Caption = #1054#1090#1085#1086#1096#1077#1085#1080#1077' BaseVolume >='
      end
      object Label3: TLabel
        Left = 193
        Top = 27
        Width = 19
        Height = 13
        Caption = 'BTC'
      end
      object Label6: TLabel
        Left = 18
        Top = 79
        Width = 125
        Height = 13
        Caption = 'BuyVolume/SellVolume >='
      end
      object Edit1: TEdit
        Left = 149
        Top = 24
        Width = 39
        Height = 21
        TabOrder = 0
        Text = '0.25'
      end
      object Edit2: TEdit
        Left = 149
        Top = 76
        Width = 39
        Height = 21
        TabOrder = 1
        Text = '1.5'
      end
      object Edit3: TEdit
        Left = 149
        Top = 51
        Width = 39
        Height = 21
        TabOrder = 2
        Text = '1.5'
      end
    end
    object GroupBox4: TGroupBox
      Left = 12
      Top = 167
      Width = 229
      Height = 64
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1094#1077#1085#1099' '#1085#1072' '#1087#1086#1082#1091#1087#1082#1091
      TabOrder = 3
      object Label9: TLabel
        Left = 15
        Top = 24
        Width = 164
        Height = 13
        Caption = 'AskPrice '#1076#1086#1083#1078#1085#1072' '#1091#1084#1077#1085#1100#1096#1080#1090#1100#1089#1103' '#1074' '
      end
      object Label10: TLabel
        Left = 15
        Top = 43
        Width = 85
        Height = 13
        Caption = #1088#1072#1079#1072' '#1080#1083#1080' '#1073#1086#1083#1100#1096#1077
      end
      object Edit6: TEdit
        Left = 185
        Top = 21
        Width = 29
        Height = 21
        TabOrder = 0
        Text = '1.3'
      end
    end
  end
  object GroupBox5: TGroupBox
    Left = 271
    Top = 111
    Width = 257
    Height = 441
    BiDiMode = bdLeftToRight
    Color = clSilver
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentBiDiMode = False
    ParentColor = False
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 5
    object Label11: TLabel
      Left = 48
      Top = 21
      Width = 76
      Height = 19
      Caption = #1048#1085#1090#1077#1088#1074#1072#1083':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 175
      Top = 21
      Width = 33
      Height = 19
      Caption = #1084#1080#1085'.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Edit7: TEdit
      Left = 130
      Top = 18
      Width = 39
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '5'
    end
    object Memo3: TMemo
      Left = 12
      Top = 237
      Width = 229
      Height = 188
      Lines.Strings = (
        'Memo1')
      TabOrder = 1
    end
    object GroupBox6: TGroupBox
      Left = 12
      Top = 51
      Width = 229
      Height = 110
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1086#1073#1098#1105#1084#1086#1074
      TabOrder = 2
      object Label13: TLabel
        Left = 23
        Top = 27
        Width = 120
        Height = 13
        Caption = #1056#1072#1079#1085#1080#1094#1072' BaseVolume >='
      end
      object Label14: TLabel
        Left = 6
        Top = 54
        Width = 137
        Height = 13
        Caption = #1054#1090#1085#1086#1096#1077#1085#1080#1077' BaseVolume >='
      end
      object Label15: TLabel
        Left = 193
        Top = 27
        Width = 19
        Height = 13
        Caption = 'BTC'
      end
      object Label16: TLabel
        Left = 18
        Top = 79
        Width = 125
        Height = 13
        Caption = 'BuyVolume/SellVolume >='
      end
      object Edit8: TEdit
        Left = 149
        Top = 24
        Width = 39
        Height = 21
        TabOrder = 0
        Text = '0.5'
      end
      object Edit9: TEdit
        Left = 149
        Top = 77
        Width = 39
        Height = 21
        TabOrder = 1
        Text = '1.5'
      end
      object Edit10: TEdit
        Left = 149
        Top = 51
        Width = 39
        Height = 21
        TabOrder = 2
        Text = '2'
      end
    end
    object GroupBox7: TGroupBox
      Left = 12
      Top = 167
      Width = 229
      Height = 64
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1094#1077#1085#1099' '#1085#1072' '#1087#1086#1082#1091#1087#1082#1091
      TabOrder = 3
      object Label17: TLabel
        Left = 15
        Top = 24
        Width = 164
        Height = 13
        Caption = 'AskPrice '#1076#1086#1083#1078#1085#1072' '#1091#1084#1077#1085#1100#1096#1080#1090#1100#1089#1103' '#1074' '
      end
      object Label18: TLabel
        Left = 15
        Top = 43
        Width = 85
        Height = 13
        Caption = #1088#1072#1079#1072' '#1080#1083#1080' '#1073#1086#1083#1100#1096#1077
      end
      object Edit11: TEdit
        Left = 185
        Top = 21
        Width = 29
        Height = 21
        TabOrder = 0
        Text = '1.6'
      end
    end
  end
  object GroupBox8: TGroupBox
    Left = 534
    Top = 111
    Width = 257
    Height = 441
    BiDiMode = bdLeftToRight
    Color = clSilver
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentBiDiMode = False
    ParentColor = False
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 6
    object Label19: TLabel
      Left = 48
      Top = 21
      Width = 76
      Height = 19
      Caption = #1048#1085#1090#1077#1088#1074#1072#1083':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label20: TLabel
      Left = 175
      Top = 21
      Width = 33
      Height = 19
      Caption = #1084#1080#1085'.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Edit12: TEdit
      Left = 130
      Top = 18
      Width = 39
      Height = 27
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '10'
    end
    object Memo4: TMemo
      Left = 12
      Top = 237
      Width = 229
      Height = 188
      Lines.Strings = (
        'Memo1')
      TabOrder = 1
    end
    object GroupBox9: TGroupBox
      Left = 12
      Top = 51
      Width = 229
      Height = 110
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1086#1073#1098#1105#1084#1086#1074
      TabOrder = 2
      object Label21: TLabel
        Left = 23
        Top = 27
        Width = 120
        Height = 13
        Caption = #1056#1072#1079#1085#1080#1094#1072' BaseVolume >='
      end
      object Label22: TLabel
        Left = 6
        Top = 54
        Width = 137
        Height = 13
        Caption = #1054#1090#1085#1086#1096#1077#1085#1080#1077' BaseVolume >='
      end
      object Label23: TLabel
        Left = 194
        Top = 27
        Width = 19
        Height = 13
        Caption = 'BTC'
      end
      object Label24: TLabel
        Left = 18
        Top = 79
        Width = 125
        Height = 13
        Caption = 'BuyVolume/SellVolume >='
      end
      object Edit13: TEdit
        Left = 149
        Top = 24
        Width = 39
        Height = 21
        TabOrder = 0
        Text = '0.1'
      end
      object Edit14: TEdit
        Left = 149
        Top = 76
        Width = 39
        Height = 21
        TabOrder = 1
        Text = '1.5'
      end
      object Edit15: TEdit
        Left = 149
        Top = 51
        Width = 39
        Height = 21
        TabOrder = 2
        Text = '2.5'
      end
    end
    object GroupBox10: TGroupBox
      Left = 12
      Top = 167
      Width = 229
      Height = 64
      Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1094#1077#1085#1099' '#1085#1072' '#1087#1086#1082#1091#1087#1082#1091
      TabOrder = 3
      object Label25: TLabel
        Left = 15
        Top = 24
        Width = 164
        Height = 13
        Caption = 'AskPrice '#1076#1086#1083#1078#1085#1072' '#1091#1084#1077#1085#1100#1096#1080#1090#1100#1089#1103' '#1074' '
      end
      object Label26: TLabel
        Left = 15
        Top = 43
        Width = 85
        Height = 13
        Caption = #1088#1072#1079#1072' '#1080#1083#1080' '#1073#1086#1083#1100#1096#1077
      end
      object Edit16: TEdit
        Left = 185
        Top = 21
        Width = 29
        Height = 21
        TabOrder = 0
        Text = '2'
      end
    end
  end
  object Button3: TButton
    Left = 919
    Top = 583
    Width = 75
    Height = 25
    Caption = 'Button3'
    TabOrder = 7
    OnClick = Button3Click
  end
  object GroupBox11: TGroupBox
    Left = 8
    Top = 8
    Width = 191
    Height = 49
    Caption = #1053#1072' '#1095#1100#1105#1084' '#1082#1086#1084#1087#1100#1102#1090#1077#1088#1077' '#1079#1072#1087#1091#1097#1077#1085#1072'?'
    Color = clSilver
    ParentBackground = False
    ParentColor = False
    TabOrder = 8
    object RadioButton3: TRadioButton
      Left = 12
      Top = 14
      Width = 158
      Height = 17
      Caption = #1050#1086#1084#1087#1100#1102#1090#1077#1088' '#1045#1075#1086#1088#1072' ('#1090#1086#1095#1082#1080')'
      TabOrder = 0
      OnClick = RadioButton3Click
    end
    object RadioButton4: TRadioButton
      Left = 12
      Top = 30
      Width = 167
      Height = 17
      Caption = #1044#1088#1091#1075#1086#1081' '#1082#1086#1084#1087#1100#1102#1090#1077#1088' ('#1079#1072#1087#1103#1090#1099#1077')'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = RadioButton4Click
    end
  end
  object Memo5: TMemo
    Left = 848
    Top = 488
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo5')
    TabOrder = 9
  end
  object GroupBox12: TGroupBox
    Left = 8
    Top = 63
    Width = 191
    Height = 42
    Caption = #1055#1072#1091#1079#1072' '#1084#1077#1078#1076#1091' '#1089#1080#1075#1085#1072#1083#1072#1084#1080' '
    Color = clSilver
    ParentBackground = False
    ParentColor = False
    TabOrder = 10
    object Label27: TLabel
      Left = 103
      Top = 19
      Width = 22
      Height = 13
      Caption = #1084#1080#1085'.'
    end
    object Edit17: TEdit
      Left = 60
      Top = 16
      Width = 37
      Height = 21
      TabOrder = 0
      Text = '5'
    end
  end
  object IdAntiFreeze1: TIdAntiFreeze
    Left = 1032
    Top = 32
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=marke' +
      'ts1.mdb;Mode=Share Deny None;Persist Security Info=False;Jet OLE' +
      'DB:System database="";Jet OLEDB:Registry Path="";Jet OLEDB:Datab' +
      'ase Password="";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locki' +
      'ng Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global B' +
      'ulk Transactions=1;Jet OLEDB:New Database Password="";Jet OLEDB:' +
      'Create System Database=False;Jet OLEDB:Encrypt Database=False;Je' +
      't OLEDB:Don'#39't Copy Locale on Compact=False;Jet OLEDB:Compact Wit' +
      'hout Replica Repair=False;Jet OLEDB:SFP=False'
    LoginPrompt = False
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 896
    Top = 96
  end
  object ADOTable1: TADOTable
    Connection = ADOConnection1
    TableName = 'cryptopiamarkets'
    Left = 896
    Top = 152
  end
  object DataSource1: TDataSource
    DataSet = ADOTable1
    Left = 968
    Top = 152
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    DataSource = DataSource1
    Parameters = <>
    Left = 1032
    Top = 152
  end
  object DataSource2: TDataSource
    DataSet = ADOTable2
    Left = 952
    Top = 224
  end
  object ADOQuery2: TADOQuery
    Connection = ADOConnection1
    DataSource = DataSource2
    Parameters = <>
    Left = 1024
    Top = 224
  end
  object ADOTable2: TADOTable
    Connection = ADOConnection1
    TableName = 'cryptopiamarkets2'
    Left = 888
    Top = 224
  end
  object MainMenu1: TMainMenu
    Left = 952
    Top = 32
    object N4: TMenuItem
      Caption = #1055#1088#1086#1082#1089#1080
      OnClick = N4Click
    end
    object N1: TMenuItem
      Caption = #1054#1090#1083#1072#1076#1082#1072
      object N3: TMenuItem
        Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1041#1044
        OnClick = N3Click
      end
    end
    object N2: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
    end
  end
  object IdFTP1: TIdFTP
    IPVersion = Id_IPv4
    ConnectTimeout = 0
    NATKeepAlive.UseKeepAlive = False
    NATKeepAlive.IdleTimeMS = 0
    NATKeepAlive.IntervalMS = 0
    ProxySettings.ProxyType = fpcmNone
    ProxySettings.Port = 0
    Left = 896
    Top = 32
  end
  object IdSSLIOHandlerSocketOpenSSL1: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvSSLv23
    SSLOptions.SSLVersions = [sslvSSLv2, sslvSSLv3, sslvTLSv1, sslvTLSv1_1, sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 1000
    Top = 368
  end
  object IdSSLIOHandlerSocketOpenSSL2: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvSSLv23
    SSLOptions.SSLVersions = [sslvSSLv2, sslvSSLv3, sslvTLSv1, sslvTLSv1_1, sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 1000
    Top = 440
  end
  object IdHTTP1: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL1
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 880
    Top = 369
  end
  object IdHTTP2: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL2
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 880
    Top = 432
  end
  object ADOTable3: TADOTable
    Connection = ADOConnection1
    TableName = 'cryptopiamarkets3'
    Left = 888
    Top = 296
  end
  object DataSource3: TDataSource
    DataSet = ADOTable3
    Left = 960
    Top = 296
  end
  object ADOQuery3: TADOQuery
    Connection = ADOConnection1
    DataSource = DataSource3
    Parameters = <>
    Left = 1032
    Top = 296
  end
  object IdHTTP3: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL3
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 880
    Top = 504
  end
  object IdSSLIOHandlerSocketOpenSSL3: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvSSLv23
    SSLOptions.SSLVersions = [sslvSSLv2, sslvSSLv3, sslvTLSv1, sslvTLSv1_1, sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 1000
    Top = 504
  end
  object IdHTTP5: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL5
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 496
    Top = 568
  end
  object IdSSLIOHandlerSocketOpenSSL4: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvSSLv23
    SSLOptions.SSLVersions = [sslvSSLv2, sslvSSLv3, sslvTLSv1, sslvTLSv1_1, sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 616
    Top = 568
  end
  object IdSSLIOHandlerSocketOpenSSL5: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvSSLv23
    SSLOptions.SSLVersions = [sslvSSLv2, sslvSSLv3, sslvTLSv1, sslvTLSv1_1, sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 792
    Top = 568
  end
  object IdHTTP4: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL4
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 416
    Top = 568
  end
end
