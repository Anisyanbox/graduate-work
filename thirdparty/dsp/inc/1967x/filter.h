extern void vcfftf(
      const float _in[],  /* (i) - pointer to input data      */
      float _out[],        /* (o) - pointer to output data     */
      const float _w[],    /* (i) - pointer to twiddle table   */
      int _wst,                 /* (i) - fft stride                 */
      int _n,                   /* (i) - fft resolution             */
      int po1[],                /* (i) - ping_pong_buffer1          */
      int po2[]                 /* (i) - ping_pong_buffer2          */
  );
