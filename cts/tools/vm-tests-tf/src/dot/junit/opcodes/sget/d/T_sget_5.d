; Copyright (C) 2008 The Android Open Source Project
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;      http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.

.source T_sget_5.java
.class public dot.junit.opcodes.sget.d.T_sget_5
.super java/lang/Object

.field public i1 I

.method public <init>()V
.limit regs 4

       invoke-direct {v3}, java/lang/Object/<init>()V

       const/4 v2, 5
       iput v2, v3, dot.junit.opcodes.sget.d.T_sget_5.i1 I
       return-void
.end method

.method public run()I
.limit regs 3

       sget v1, dot.junit.opcodes.sget.d.T_sget_5.i1 I
       return v1
.end method


