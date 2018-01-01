// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

var LibAl = {
    $AL: {
      buffers: {},
      lastBufferIdx: 0,
      sources: {},
      lastSourceIdx: 0,
    },
  
    alInit: function() {
      AL.context = undefined;
      try {
        window.AudioContext = window.AudioContext || window.webkitAudioContext;
        AL.context = new AudioContext();
      }
      catch(e) {
        console.log('Web Audio API is not supported in this browser');
      }
      if(AL.context) {
        return 0;
      }
      return 1;
    },
  
    alBufferData: function(n_channels, sample_rate, data, sample_count) {
      var buffer = AL.context.createBuffer(n_channels, sample_count, sample_rate);
      for(var ch = 0; ch < n_channels; ch++) {
        var buffer_data = buffer.getChannelData(ch);
        for(var i = 0; i < sample_count/n_channels; i++) {
          buffer_data[i] = getValue(data + ch*4 + i*(n_channels)*4, 'float');
        }
      }
      AL.lastBufferIdx += 1;
      AL.buffers[AL.lastBufferIdx] = buffer;
      return AL.lastBufferIdx;
    },
  
    alDestroyBuffer: function(bufferIdx) {
      AL.buffers[bufferIdx] = undefined;
      delete AL.buffers[bufferIdx];
    },
  
    alPlay: function(bufferIdx, mode) {
      var source = AL.context.createBufferSource();
      source.buffer = AL.buffers[bufferIdx];
      source.connect(AL.context.destination);
      if (mode == 1) {
        source.loop = true;
      }
      source.start();
  
      AL.lastSourceIdx += 1;
      AL.sources[AL.lastSourceIdx] = source;
  
      (function(sourceIdx, source) {
        source.onended = function() {
          source.disconnect();
          AL.sources[sourceIdx] = undefined;
          delete AL.sources[sourceIdx];
        };
      })(AL.lastSourceIdx, source);
      return AL.lastSourceIdx;
  
    },
  
    alStop: function(sourceIdx) {
      var source = AL.sources[sourceIdx];
      if(source) {
        source.stop();
        AL.sources[sourceIdx] = undefined;
        delete AL.sources[sourceIdx];
      }
    },
  
    alSuspend: function() {
      AL.context.suspend();
    },
  
    alResume: function() {
      AL.context.resume();
    },
  };
  
  autoAddDeps(LibAl, '$AL');
  mergeInto(LibraryManager.library, LibAl);